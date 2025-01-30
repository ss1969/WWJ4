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
#include <stdlib.h>

#define MaxLenStr 80

/* String convert to lower case */
void Str2Lwr(char *str) {
    int     i;
    uint8_t ch = 0;

    if (str == NULL)
        return;
    for (i = 0; *(str + i) != '\0'; i++) {
        if (ch >= 'A' && ch <= 'Z')
            *(str + i) = ch - 'A' + 'a';
    }
}

/* String convert to upper case */
void Str2Upr(char *str) {
    int     i;
    uint8_t ch = 0;

    if (str == NULL)
        return;
    for (i = 0; *(str + i) != '\0'; i++) {
        if (ch >= 'a' && ch <= 'z')
            *(str + i) = ch - 'a' + 'A';
    }
}

#define CONVERT_TO_TYPE(s1, s2)                                                                                        \
    if (str == NULL)                                                                                                   \
        return 0;                                                                                                      \
    if (sscanf(str, s1, num) == 1) {                                                                                   \
        return 1;                                                                                                      \
    }                                                                                                                  \
    Str2Lwr(str);                                                                                                      \
    if (sscanf(str, s2, num) == 1) {                                                                                   \
        return 1;                                                                                                      \
    }                                                                                                                  \
    return 0;

/* string convert to number; default dec. */
uint8_t Str2Dec32(char *str, uint32_t *num) {
    CONVERT_TO_TYPE("%u", "0d%u");
}

uint8_t Str2Dec64(char *str, uint64_t *num) {
    CONVERT_TO_TYPE("%llu", "0d%llu");
}

/* string convert to number; default hex. */
uint8_t Str2Hex32(char *str, uint32_t *num) {
    CONVERT_TO_TYPE("%x", "0x%x");
}

/* string convert to number; default hex. */
uint8_t Str2Hex64(char *str, uint64_t *num) {
    CONVERT_TO_TYPE("%llx", "0x%llx");
}

/* Bit Str to number */
uint8_t Str2Binary(char *str, uint8_t *Num) {
    uint16_t i = 0;
    uint8_t  ch;
    uint8_t  x = 0;

    if (str == NULL)
        return 0;

    ch = str[i];
    while ((ch != '\0') && (i < MaxLenStr)) {
        if (ch == '0' || ch == '1') {
            if (ch == '1') {
                if (i > 7)
                    return 0;
                x |= (0x01 << (7 - i));
            }
        }
        else
            return 0;
        i  = i + 1;
        ch = str[i];
    }

    if (i < MaxLenStr || str[MaxLenStr] == '\0') {
        *Num = x;
        return 1;
    }
    else
        return 0;
}

// 连续的HEX字符串转成unicode，"3010652F4ED8" =>"\u3010\u652F\u4ED8"
char *convertToUnicode(const char *hexStr) {
    if (hexStr == NULL || strlen(hexStr) % 4 != 0) {
        printf("Length not correct\n");
        return NULL;
    }

    size_t hexLen      = strlen(hexStr);
    size_t unicode_len = hexLen / 4;
    char  *unicode_str = (char *)malloc((unicode_len * 3 + 1) * sizeof(char)); // UTF-8编码可能需要最多3个字节
    if (unicode_str == NULL) {
        printf("memory lock fail\n");
        return NULL;
    }

    char *ptr = unicode_str;
    for (size_t i = 0; i < hexLen; i += 4) {
        unsigned int code_point;
        sscanf(hexStr + i, "%4X", &code_point);

        if (code_point <= 0x7F) {
            *ptr++ = code_point;
        }
        else if (code_point <= 0x7FF) {
            *ptr++ = 0xC0 | ((code_point >> 6) & 0x1F);
            *ptr++ = 0x80 | (code_point & 0x3F);
        }
        else {
            *ptr++ = 0xE0 | ((code_point >> 12) & 0x0F);
            *ptr++ = 0x80 | ((code_point >> 6) & 0x3F);
            *ptr++ = 0x80 | (code_point & 0x3F);
        }
    }
    *ptr = '\0';

    return unicode_str;
}