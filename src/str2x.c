/************************************************************************
 * Copyright(c) 2016
 *
 * Auther: Kiilii Lee
 *
 * The copyright notice above does not evidence any actual or intended
 * publication of such source code
 ************************************************************************
 */
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MaxLenStr 80


/* String convert to lower case */
void Str2Lwr(char *str)
{
	int i;
	uint8_t ch = 0;

	if(str == NULL) return;
	for(i = 0; *(str + i) != '\0'; i++){
		if(ch >= 'A' && ch <= 'Z') *(str+i) = ch - 'A' + 'a';
	}
}

/* String convert to upper case */
void Str2Upr(char *str)
{
	int i;
	uint8_t ch = 0;

	if(str == NULL) return;
	for(i = 0; *(str + i) != '\0'; i++){
		if(ch >= 'a' && ch <= 'z') *(str+i) = ch - 'a' + 'A';
	}
}

#define CONVERT_TO_TYPE(s1, s2)				\
	if(str == NULL) return 0;				\
	if(sscanf(str, s1, num) == 1){			\
		return 1;							\
	}										\
	Str2Lwr(str);							\
	if(sscanf(str, s2, num) == 1){			\
		return 1;							\
	}										\
	return 0;


/* string convert to number; default dec. */
uint8_t Str2Dec32(char *str, uint32_t *num)
{
	CONVERT_TO_TYPE("%u", "0d%u");
}

uint8_t Str2Dec64(char *str, uint64_t *num)
{
	CONVERT_TO_TYPE("%llu", "0d%llu");
}

/* string convert to number; default hex. */
uint8_t Str2Hex32(char *str, uint32_t *num)
{
	CONVERT_TO_TYPE("%x", "0x%x");
}

/* string convert to number; default hex. */
uint8_t Str2Hex64(char *str, uint64_t *num)
{
	CONVERT_TO_TYPE("%llx", "0x%llx");
}

/* Bit Str to number */
uint8_t Str2Binary(char *str, uint8_t *Num)
{
	uint16_t i=0;
	uint8_t ch;
	uint8_t  x = 0;

	if(str == NULL) return 0;

	ch = str[i];
	while((ch != '\0') && (i < MaxLenStr)){
		if(ch=='0'||ch=='1'){
			if(ch == '1'){
				if(i>7) return 0;
				x |= (0x01 << (7-i));
			}
		}
		else return 0;
		i = i + 1;
		ch = str[i];
	}

	if(i < MaxLenStr || str[MaxLenStr] == '\0'){
		*Num = x;
		return 1;
	}
	else return 0;

}

