#ifndef _LCD_DRV_H_
#define _LCD_DRV_H_

#include "luat_lcd.h"

#define LCD_WIDTH  240
#define LCD_HEIGHT 320

void lcd_init(void);
void lcd_draw(int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t *color);

#endif
