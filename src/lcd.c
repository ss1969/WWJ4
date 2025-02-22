#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "luat_spi.h"
#include "luat_lcd.h"
#include "luat_gpio.h"
#include "soc_spi.h"

#include "lcd.h"
#include "st7789v.h"

#define LCD_SPI SPI_ID0
#define LCD_CS  HAL_GPIO_8
#define LCD_TE  HAL_GPIO_2
#define LCD_RST HAL_GPIO_1
#define LCD_PWR HAL_GPIO_24

luat_rtos_task_handle task_lcd_handle;

static luat_spi_device_t lcd_spi_dev = {.bus_id              = LCD_SPI,
                                        .spi_config.id       = LCD_SPI,
                                        .spi_config.CPHA     = 1,
                                        .spi_config.CPOL     = 1,
                                        .spi_config.dataw    = 8,
                                        .spi_config.bit_dict = 1,
                                        .spi_config.master   = 1,
                                        .spi_config.mode     = 1,
                                        .spi_config.bandrate = 51 * 1000000,
                                        .spi_config.cs       = LCD_CS};

luat_lcd_conf_t lcd_conf = {.port           = LUAT_LCD_SPI_DEVICE,
                            .lcd_spi_device = &lcd_spi_dev,
                            .opts           = &lcd_opts_st7789v,
                            .interface_mode = LUAT_LCD_IM_3_WIRE_9_BIT_INTERFACE_I,
                            .auto_flush     = 1,
                            .pin_dc         = LUAT_GPIO_NONE,
                            .pin_rst        = LCD_RST,
                            .pin_pwr        = LCD_PWR,
                            .lcd_cs_pin     = LCD_CS,
                            .direction      = SCREEN_DIRECTION,
                            .w              = LCD_WIDTH,
                            .h              = LCD_HEIGHT,
                            .xoffset        = 0,
                            .yoffset        = 0};

void lcd_init(void) {
    luat_spi_device_setup(&lcd_spi_dev);
    luat_lcd_init(&lcd_conf);
    st7789v_set_direction(&lcd_conf);
    luat_lcd_clear(&lcd_conf, LCD_BLACK);
}

void lcd_draw(int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t *color) {
    lcd_draw_3w9bt1(&lcd_conf, x1, y1, x2, y2, color);
}
