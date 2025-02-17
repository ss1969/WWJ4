#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_

#include "luat_lcd.h"

#define LCD_DIRECTION 1

#if LCD_DIRECTION == 0 || LCD_DIRECTION == 2
#define LCD_WIDTH  240
#define LCD_HEIGHT 320
#elif LCD_DIRECTION == 1 || LCD_DIRECTION == 3
#define LCD_WIDTH  320
#define LCD_HEIGHT 240
#else
#error "LCD_DIRECTION ERROR: Invalid value for LCD_DIRECTION. It must be 0, 1, 2, or 3."
#endif

void lcd_init(void);
void lcd_draw(int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t *color);

#endif
