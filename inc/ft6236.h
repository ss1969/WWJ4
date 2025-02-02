#ifndef _FT6236_H_
#define _FT6236_H_

bool tp_is_pressed(void);
void tp_get_data(int16_t *x, int16_t *y);
void tp_taskinit(void);

#endif