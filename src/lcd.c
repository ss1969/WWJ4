#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "luat_spi.h"
#include "luat_lcd.h"
#include "luat_gpio.h"

#include "usart.h"
#include "st7789v.h"

#define LCD_SPI	    SPI_ID0
#define LCD_CS	    HAL_GPIO_8
#define LCD_TE	    HAL_GPIO_2
#define LCD_RST	    HAL_GPIO_1
#define LCD_PWR	    HAL_GPIO_24

luat_rtos_task_handle lcd_task_handle;

static luat_spi_device_t lcd_spi_dev = {
    .bus_id = LCD_SPI,
    .spi_config.id = LCD_SPI,
    .spi_config.CPHA = 1,
    .spi_config.CPOL = 1,
    .spi_config.dataw = 8,
    .spi_config.bit_dict = 1,
    .spi_config.master = 1,
    .spi_config.mode = 1,
    .spi_config.bandrate = 51 * 1000000,
    .spi_config.cs = LCD_CS
};

static luat_lcd_conf_t lcd_conf = {
    .port = LUAT_LCD_SPI_DEVICE,
    .lcd_spi_device = &lcd_spi_dev,
    .opts = &lcd_opts_st7789v,
    .interface_mode = LUAT_LCD_IM_3_WIRE_9_BIT_INTERFACE_I,
    .auto_flush = 1,
    .pin_dc = LUAT_GPIO_NONE,
    .pin_rst = LCD_RST,
    .pin_pwr = LCD_PWR,
    .lcd_cs_pin = LCD_CS,
    .direction = 0,
    .w = ST7789V_W,
    .h = ST7789V_H,
    .xoffset = 0,
    .yoffset = 0
};

#define RED         0xF800
#define GREEN       0x07E0
#define BLUE       	0x001F

static void task_test_lcd(void *param)
{
    luat_spi_device_setup(&lcd_spi_dev);
    luat_lcd_init(&lcd_conf);
    st7789v_set_direction(&lcd_conf);

    luat_lcd_clear(&lcd_conf,LCD_WHITE);

        luat_lcd_draw_line(&lcd_conf,20,35,140,35,0x001F);
        luat_lcd_draw_rectangle(&lcd_conf,20,40,120,70,0xF800);
        luat_lcd_draw_circle(&lcd_conf,60,60,10,0x0CE0);
        luat_lcd_flush(&lcd_conf);
    while (1){
        luat_rtos_task_sleep(1000);
    }
}

void lcd_taskinit(void)
{
    luat_rtos_task_create(&lcd_task_handle, 4096, 20, "lcd", task_test_lcd, NULL, 0);
}
