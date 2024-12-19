#ifndef _STR2_X_H_
#define _STR2_X_H_

#include <stdint.h>

void Str2Lwr(char *str);
void Str2Upr(char *str);

uint8_t Str2Dec32(char *str, uint32_t *num);
uint8_t Str2Dec64(char *str, uint64_t *num);
uint8_t Str2Hex32(char *str, uint32_t *num);
uint8_t Str2Hex64(char *str, uint64_t *num);

uint8_t Str2Binary(char *str, uint8_t *Num);

#endif

