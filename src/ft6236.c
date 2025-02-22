#include "common_api.h"
#include "luat_base.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "luat_i2c.h"
#include "luat_mcu.h"
#include "luat_gpio.h"

#include "ft6236.h"
#include "wrapper.h"
#include "lcd.h"

// FT6336 部分寄存器定义
// 6236 和 6336 区别在于6336支持5个触摸点
#define FT6336_ADDR  0x38
#define TP_RST_PIN   HAL_GPIO_22
#define TP_INT_PIN   HAL_GPIO_36
#define TP_I2C_INDEX 0

typedef enum FT6336_MODE_E {
    FT6336_MODE_OP = 0,
    FT6336_MODE_TE = 0x40,
    FT6336_MODE_SY = 0x10,
} FT6336_MODE;

typedef enum {
    FT6336_DEVICE_MODE   = 0x00,
    FT6336_GET_FINGERNUM = 0x02,
    FT6336_GET_LOC0      = 0x03,
    FT6336_GET_LOC1      = 0x09,
} FT6336_REG_OP;

// Variables
luat_rtos_task_handle task_tp_handle;
static bool           is_pressed = false;
static int16_t        xy_pos[4]  = {0};

bool tp_is_pressed(void) {
    return is_pressed;
}

void tp_get_data(int16_t *x, int16_t *y) {
    *x         = xy_pos[0];
    *y         = xy_pos[1];
    is_pressed = false;
}

static inline int tp_int_cb(int pin, void *args) {
    if (pin == TP_INT_PIN) {
        luat_rtos_event_send(task_tp_handle, 0, 0, 0, 0, 0);
    }
    return 0;
}

static inline int ft6336_read(uint8_t regAddr, uint8_t *buf, uint8_t len) {
    return luat_i2c_read_reg(TP_I2C_INDEX, FT6336_ADDR, regAddr, buf, len);
}

static inline int ft6336_write(uint8_t regAddr, uint8_t data) {
    return luat_i2c_write_reg(TP_I2C_INDEX, FT6336_ADDR, regAddr, &data, 1, 1);
}

static inline void ft6336_setmode(FT6336_MODE mode) {
    ft6336_write(FT6336_DEVICE_MODE, mode);
}

static inline uint8_t ft6336_scan(int16_t *pos) {
    uint8_t temp[8]    = {0};
    uint8_t finger_num = 0;

    ft6336_read(FT6336_GET_FINGERNUM, &finger_num, 1);
    if (finger_num) {
        ft6336_read(FT6336_GET_LOC0, temp, 4);
#if SCREEN_DIRECTION == 0
        pos[0] = ((uint16_t)(temp[0] & 0x0F) << 8) + temp[1];
        pos[1] = (((uint16_t)(temp[2] & 0x0F) << 8) + temp[3]);
#elif SCREEN_DIRECTION == 1
        pos[1] = LCD_HEIGHT - (((uint16_t)(temp[0] & 0x0F) << 8) + temp[1]);
        pos[0] = (((uint16_t)(temp[2] & 0x0F) << 8) + temp[3]);
#elif SCREEN_DIRECTION == 2
        pos[0] = LCD_WIDTH - (((uint16_t)(temp[0] & 0x0F) << 8) + temp[1]);
        pos[1] = LCD_HEIGHT - (((uint16_t)(temp[2] & 0x0F) << 8) + temp[3]);
#elif SCREEN_DIRECTION == 3
        pos[1] = ((uint16_t)(temp[0] & 0x0F) << 8) + temp[1];
        pos[0] = LCD_WIDTH - (((uint16_t)(temp[2] & 0x0F) << 8) + temp[3]);
#endif
        // LOG("Touch#1 %d,%d", pos[0], pos[1]);
        if (finger_num > 1) {
            ft6336_read(FT6336_GET_LOC1, &temp[4], 4);
#if SCREEN_DIRECTION == 0
            pos[2] = ((uint16_t)(temp[4] & 0x0F) << 8) + temp[5];
            pos[3] = (((uint16_t)(temp[6] & 0x0F) << 8) + temp[7]);
#elif SCREEN_DIRECTION == 1
            pos[3] = LCD_HEIGHT - (((uint16_t)(temp[4] & 0x0F) << 8) + temp[5]);
            pos[2] = (((uint16_t)(temp[6] & 0x0F) << 8) + temp[7]);
#elif SCREEN_DIRECTION == 2
            pos[2] = LCD_WIDTH - (((uint16_t)(temp[4] & 0x0F) << 8) + temp[5]);
            pos[3] = LCD_HEIGHT - (((uint16_t)(temp[6] & 0x0F) << 8) + temp[7]);
#elif SCREEN_DIRECTION == 3
            pos[3] = ((uint16_t)(temp[4] & 0x0F) << 8) + temp[5];
            pos[2] = LCD_WIDTH - (((uint16_t)(temp[6] & 0x0F) << 8) + temp[7]);
#endif
            // LOG("Touch#2 %d,%d", pos[2], pos[3]);
        }
    }
    return finger_num;
}

static void touchpad_main_routine(void *param) {

    // int & reset
    luat_gpio_cfg_t cfg = {0};
    cfg.pin             = TP_RST_PIN;
    cfg.mode            = LUAT_GPIO_OUTPUT;
    cfg.output_level    = 1;
    luat_gpio_open(&cfg);

    cfg.pin      = TP_INT_PIN;
    cfg.mode     = LUAT_GPIO_IRQ;
    cfg.pull     = LUAT_GPIO_PULLUP;
    cfg.irq_type = LUAT_GPIO_FALLING_IRQ;
    cfg.irq_cb   = tp_int_cb;
    luat_gpio_open(&cfg);

    // reset chip
    luat_gpio_set(TP_RST_PIN, 0);
    luat_rtos_task_sleep(10);
    luat_gpio_set(TP_RST_PIN, 1);

    // init i2c, 这里使用I2C0，由paddr 13、14 mux
    luat_mcu_iomux_ctrl(LUAT_MCU_PERIPHERAL_I2C, TP_I2C_INDEX, 13, 2, 0);
    luat_mcu_iomux_ctrl(LUAT_MCU_PERIPHERAL_I2C, TP_I2C_INDEX, 14, 2, 0);
    luat_i2c_setup(TP_I2C_INDEX, 1);

    // task
    luat_event_t event;
    while (true) {
        luat_rtos_event_recv(task_tp_handle, 0, &event, NULL, LUAT_WAIT_FOREVER);
        is_pressed = ft6336_scan(xy_pos) > 0;
    }
}

void tp_task_init(void) {
    luat_rtos_task_create(&task_tp_handle, 2048, 20, "task_tp", touchpad_main_routine, NULL, 16);
}