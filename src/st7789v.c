#include "common_api.h"
#include "luat_debug.h"

#include "luat_spi.h"
#include "luat_lcd.h"
#include "luat_gpio.h"

#include "usart.h"

#define BULK_SIZE 36 // 9bit一个数据，所以定义36B的buffer可以存32个数据

/* 3WIRE 9BIT MODE1, 320x240 */
static const uint16_t st7789v_init_cmds[] = {
    /* RGB 5-6-5-bit  */
    0x023A,
    0x0305,
    /* Porch Setting */
    0x02B2,
    0x030C,
    0x030C,
    0x0300,
    0x0333,
    0x0333,
    /*  Gate Control */
    0x02B7,
    0x0335,
    /* VCOM Setting */
    0x02BB,
    0x0317,
    /* LCM Control */
    0x02C0,
    0x032C,
    /* VDV and VRH Command Enable */
    0x02C2,
    0x0301,
    /* VRH Set */
    0x02C3,
    0x0312,
    /* VDV Set */
    0x02C4,
    0x0320,
    /* Frame Rate Control in Normal Mode */
    0x02C6,
    0x030F,
    /* Power Control 1 */
    0x02D0,
    0x03A4,
    0x03A1,
    /* Positive Voltage Gamma Control */
    0x02E0,
    0x03D0,
    0x0304,
    0x030D,
    0x0311,
    0x0313,
    0x032B,
    0x033F,
    0x0354,
    0x034C,
    0x0318,
    0x030D,
    0x030B,
    0x031F,
    0x0323,
    /* Negative Voltage Gamma Control */
    0x02E1,
    0x03D0,
    0x0304,
    0x030C,
    0x0311,
    0x0313,
    0x032C,
    0x033F,
    0x0344,
    0x0351,
    0x032F,
    0x031F,
    0x031F,
    0x0320,
    0x0323,
    /* Display Inversion On */
    0x0221,
};

static inline void select_cs(luat_lcd_conf_t *conf) {
    if (conf->lcd_cs_pin != LUAT_GPIO_NONE)
        luat_gpio_set(conf->lcd_cs_pin, 0);
}

static inline void deselect_cs(luat_lcd_conf_t *conf) {
    if (conf->lcd_cs_pin != LUAT_GPIO_NONE)
        luat_gpio_set(conf->lcd_cs_pin, 1);
}

static inline void write_16b_3w9bt1(luat_lcd_conf_t *conf, uint16_t data) {
    select_cs(conf);
    uint8_t buf[3] = {
        0x80 | (data & 0xFF00) >> 9,                      // DC=1,data[15:9]
        0x40 | (data & 0x0100) >> 1 | (data & 0xFC) >> 2, // data[8], DC=1, data[7:2]
        (data & 0x03) << 6,                               // data[1:0]
    };
    // uart_print_async("[%02x %02x %02x]", buf[0], buf[1], buf[2]);
    luat_spi_send(conf->lcd_spi_device->spi_config.id, (const char *)buf, sizeof(buf));
    deselect_cs(conf);
}

static int write_cmd_data_3w9bt1(luat_lcd_conf_t *conf, const uint8_t cmd, const uint8_t *data, uint8_t data_len) {
#if 0
    uart_print_async("CMD %02x", cmd);
    if(data_len){
        uart_print_async(", DATA ");
        for(int i = 0; i < data_len; i++) uart_print_async("%02x ", data[i]);
    }
    uart_print_async("\n");
#endif
    uint8_t buf[36]    = {0};
    int     buf_index  = 0;
    int     data_index = 0;
    int     shift      = 7; // DC bit需要向 << 多少位，同时也是data 位移计算值

    if (cmd != 0) {
        buf[buf_index] = cmd >> 1; // cmd, DC位 == 0,填入cmd上半
        buf_index++;               // buf位置+1
        buf[buf_index] = cmd << 7; // 填入cmd下半，但是buf位置不变
        shift--;
    }

    select_cs(conf);
    while (data_index != data_len) {
        buf[buf_index] |= 0x1 << shift;                    // 填入DC位 == 1
        buf[buf_index] |= data[data_index] >> (8 - shift); // 填入data上半部分，右移
        buf_index++;                                       // data后半部分必然是下一个buffer位置了
        buf[buf_index] |= data[data_index] << shift;       // 填入data后半部分
        if (shift == 0)
            buf_index++;                    // shift == 0表示 data[data_index] 完全填满了上一个buffer位置了
        data_index++;                       // 可以取下一个数据了
        shift = shift == 0 ? 7 : shift - 1; // 计算下次 shift 值
        if (buf_index == BULK_SIZE) {       // 填满了就发送一次
            luat_spi_send(conf->lcd_spi_device->spi_config.id, (const char *)buf, buf_index);
            buf_index = 0;
        }
    }

    if (buf_index) { // 剩余有数据也发送，多1个byte
        luat_spi_send(conf->lcd_spi_device->spi_config.id, (const char *)buf, buf_index + 1);
    }

    deselect_cs(conf);
    return 0;
}

void lcd_draw_3w9bt1(luat_lcd_conf_t *conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t *color) {
    // uart_print_async("draw (%d.%d)(%d.%d) 0x%04x\n", x1, y1, x2, y2, *color);

    // RASET
    uint8_t bufx[4] = {x1 >> 8, x1 & 0xFF, x2 >> 8, x2 & 0xFF};
    write_cmd_data_3w9bt1(conf, 0x2A, bufx, sizeof(bufx));

    // CASET
    uint8_t bufy[4] = {y1 >> 8, y1 & 0xFF, y2 >> 8, y2 & 0xFF};
    write_cmd_data_3w9bt1(conf, 0x2B, bufy, sizeof(bufy));

    // 开始写入内存
    write_cmd_data_3w9bt1(conf, 0x2C, NULL, 0);

    // 发送颜色数据
    int pixel_count = (x2 - x1 + 1) * (y2 - y1 + 1);
    for (int i = 0; i < pixel_count; i++) {
        write_16b_3w9bt1(conf, color[i]);
    }
}

int st7789v_set_direction(luat_lcd_conf_t *conf) {
    uint8_t direction_data = 0;
    if (conf->direction == 0)
        direction_data = conf->opts->direction0;
    else if (conf->direction == 1)
        direction_data = conf->opts->direction90;
    else if (conf->direction == 2)
        direction_data = conf->opts->direction180;
    else
        direction_data = conf->opts->direction270;
    if (conf->direction == 1 || conf->direction == 3) {
        int t   = conf->w;
        conf->w = conf->h;
        conf->h = t;
    }
    uart_print_async("LCD direction %d, width %d, height %d\n", conf->direction, conf->w, conf->h);
    lcd_write_cmd_data(conf, 0x36, &direction_data, 1);
    return 0;
}

static void init_3w9bt1(luat_lcd_conf_t *conf) {
    size_t  i   = 0;
    uint8_t cmd = 0;
    uint8_t data[32];
    size_t  data_len = 0;

    while (i < conf->opts->init_cmds_len) {
        uint16_t current = conf->opts->init_cmds[i++];
        uint8_t  type    = (current >> 8) & 0xFF;
        uint8_t  value   = current & 0xFF;

        switch (type) {
            case 0:
            case 2: // 命令
                // 如果有之前的数据，先发送
                if (data_len > 0) {
                    write_cmd_data_3w9bt1(conf, cmd, data, data_len);
                    data_len = 0;
                }
                cmd = value;
                break;
            case 3: // 数据
                data[data_len++] = value;
                break;
            case 1:
                luat_rtos_task_sleep(value);
                break;
        }

        // 如果是最后一个元素或下一个元素是新命令，发送当前命令和数据
        if (i == conf->opts->init_cmds_len || (conf->opts->init_cmds[i] >> 8) == 0x02) {
            write_cmd_data_3w9bt1(conf, cmd, data, data_len);
            data_len = 0;
        }
    }
}

luat_lcd_opts_t lcd_opts_st7789v = {.name           = "st7789v",
                                    .init_cmds_len  = sizeof(st7789v_init_cmds) / sizeof(st7789v_init_cmds[0]),
                                    .init_cmds      = st7789v_init_cmds,
                                    .init           = init_3w9bt1,
                                    .direction0     = 0x00,
                                    .direction90    = 0x60,
                                    .direction180   = 0xC0,
                                    .direction270   = 0xA0,
                                    .rb_swap        = 1,
                                    .write_cmd_data = write_cmd_data_3w9bt1,
                                    .lcd_draw       = lcd_draw_3w9bt1};
