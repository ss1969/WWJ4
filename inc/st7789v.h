#ifndef _ST7789V_H_
#define _ST7789V_H_

#define ST7789V_H   320
#define ST7789V_W   240

extern luat_lcd_opts_t lcd_opts_st7789v;
void lcd_draw_3w9bt1(luat_lcd_conf_t* conf, int16_t x1, int16_t y1, int16_t x2, int16_t y2, luat_color_t* color);
int st7789v_set_direction(luat_lcd_conf_t* conf);
#endif