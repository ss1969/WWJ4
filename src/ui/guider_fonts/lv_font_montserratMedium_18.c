/*******************************************************************************
 * Size: 16 px
 * Bpp: 2
 * Opts: --bpp 2 --size 16 --font Montserrat-Medium.ttf --symbols  =！@#￥%……&*()~:"{}[]|\?/<>,.;'+1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ --format lvgl -o lv_font_montserratMedium_18.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_FONT_MONTSERRATMEDIUM_18
#define LV_FONT_MONTSERRATMEDIUM_18 1
#endif

#if LV_FONT_MONTSERRATMEDIUM_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0022 "\"" */
    0x39, 0xc3, 0xff, 0x91, 0x46, 0x0,

    /* U+0023 "#" */
    0x9, 0xc2, 0xd0, 0xec, 0x24, 0x43, 0xff, 0x87,
    0xe4, 0xf4, 0x78, 0xa, 0x2, 0x80, 0xa0, 0x50,
    0x68, 0x34, 0xe, 0xc3, 0xe6, 0x85, 0x43, 0x26,
    0xa0, 0x28, 0xe, 0x5c, 0x7a, 0x2e, 0xb, 0xe,
    0x43, 0xff, 0x86,

    /* U+0025 "%" */
    0x7, 0xc8, 0x67, 0x83, 0x64, 0xc1, 0xa2, 0x9,
    0x36, 0x10, 0x66, 0x1f, 0xec, 0x44, 0x3f, 0xec,
    0x88, 0x39, 0x21, 0x1c, 0xdf, 0x41, 0x4f, 0x44,
    0x55, 0x4c, 0x7, 0xe6, 0x2d, 0x69, 0xf, 0x66,
    0x1c, 0x87, 0xa2, 0xf, 0x21, 0xe4, 0x41, 0xad,
    0x21, 0xb3, 0x9, 0xa9, 0x80,

    /* U+0026 "&" */
    0xa, 0xf4, 0x1e, 0x5a, 0x70, 0xec, 0x94, 0x1f,
    0xe4, 0x3d, 0x96, 0x41, 0xc8, 0x9a, 0x1d, 0x87,
    0x21, 0x67, 0x8c, 0xb0, 0x90, 0x66, 0x41, 0x21,
    0x20, 0x40, 0x9d, 0xa0, 0xc1, 0x41, 0x2e, 0x10,
    0x3f, 0x23, 0xa0,

    /* U+0027 "'" */
    0x38, 0x3f, 0xd4,

    /* U+0028 "(" */
    0x7, 0x81, 0x10, 0x11, 0x11, 0x6, 0x61, 0x90,
    0x21, 0xff, 0xc2, 0x44, 0x19, 0x81, 0x10, 0xfd,
    0x10, 0x1b, 0x0,

    /* U+0029 ")" */
    0x3c, 0x12, 0x20, 0xcc, 0x8, 0x87, 0xe4, 0x43,
    0xff, 0x94, 0x88, 0x79, 0x20, 0x42, 0xa, 0x0,

    /* U+002A "*" */
    0x4, 0x81, 0xdf, 0xa, 0x18, 0x50, 0x21, 0xda,
    0x5, 0x28,

    /* U+002B "+" */
    0xa, 0x81, 0xff, 0xc7, 0x7c, 0xaf, 0x2e, 0x2,
    0xc5, 0x15, 0x40, 0xff, 0xe0, 0x50, 0x20,

    /* U+002C "," */
    0x24, 0x60, 0x28, 0x80,

    /* U+002E "." */
    0x10, 0x58, 0x10,

    /* U+002F "/" */
    0xf, 0x41, 0xe9, 0xf, 0x21, 0xe4, 0x83, 0xb1,
    0xe, 0x43, 0xc9, 0x7, 0x62, 0x1c, 0x87, 0x91,
    0xe, 0xc8, 0x39, 0xf, 0x22, 0x1d, 0x90, 0x72,
    0x1f, 0x90, 0xe0,

    /* U+0030 "0" */
    0xa, 0xf4, 0x1d, 0xa0, 0x70, 0xa1, 0xf2, 0x40,
    0x48, 0x10, 0x87, 0xfc, 0x87, 0xff, 0x1d, 0xf,
    0xfe, 0x42, 0x40, 0x84, 0x10, 0xf9, 0x20, 0xb4,
    0xe, 0x0,

    /* U+0031 "1" */
    0x7f, 0x7, 0xcf, 0x83, 0xff, 0xda,

    /* U+0032 "2" */
    0x3, 0xf4, 0x1b, 0x82, 0x70, 0xcf, 0xc0, 0x81,
    0xc1, 0x21, 0xfc, 0x90, 0x7b, 0x10, 0xf4, 0x8,
    0x3a, 0x4c, 0x39, 0x46, 0x1c, 0xc6, 0x1e, 0x81,
    0xfc, 0x1f, 0xf0,

    /* U+0033 "3" */
    0x3f, 0xe4, 0x3f, 0x27, 0xe0, 0x41, 0xd9, 0x21,
    0xb2, 0x43, 0x20, 0xb4, 0x26, 0x89, 0x21, 0x2a,
    0x86, 0x1f, 0x93, 0x42, 0xc6, 0x2f, 0x92, 0xa4,
    0x27, 0x0,

    /* U+0034 "4" */
    0xd, 0xe0, 0xf9, 0x10, 0xfa, 0x20, 0xf4, 0x21,
    0xf2, 0x42, 0x82, 0x84, 0x14, 0x9, 0x20, 0xf2,
    0xf, 0x81, 0xa1, 0xfe, 0x7f, 0x81, 0xa1, 0xff,
    0xc8,

    /* U+0035 "5" */
    0x2f, 0xf4, 0x1f, 0xfc, 0x2b, 0xf4, 0x1f, 0xfc,
    0x2b, 0xd0, 0x7f, 0x3a, 0xb, 0xf0, 0x20, 0xfa,
    0xf, 0xfe, 0x16, 0x85, 0x4, 0x97, 0xc0, 0xc7,
    0x42, 0x70, 0x0,

    /* U+0036 "6" */
    0x9, 0xfa, 0x42, 0xa0, 0x4c, 0x5, 0x1f, 0xc0,
    0x8c, 0x3f, 0xd5, 0x21, 0xda, 0xd2, 0x1d, 0xe8,
    0x83, 0x60, 0x50, 0x87, 0xfc, 0x90, 0x14, 0x24,
    0x3e, 0x84, 0x2d, 0xa, 0x80,

    /* U+0037 "7" */
    0x7f, 0xf2, 0x1f, 0xfc, 0x7, 0xe8, 0xb, 0x61,
    0x62, 0x9, 0x9, 0x20, 0xf4, 0x21, 0xf2, 0x41,
    0xe8, 0x3f, 0x92, 0xf, 0x20, 0x43, 0xd1, 0x7,
    0x90, 0x21, 0x80,

    /* U+0038 "8" */
    0x3, 0xf4, 0x19, 0x85, 0xb0, 0xa3, 0xa8, 0x83,
    0xe4, 0x34, 0x40, 0x8c, 0xb, 0x79, 0x60, 0x28,
    0x32, 0x81, 0x1f, 0x88, 0x44, 0x3f, 0x90, 0xf9,
    0x7, 0xe1, 0x7, 0x6, 0xa0,

    /* U+0039 "9" */
    0x3, 0xf4, 0x1a, 0x81, 0x38, 0x49, 0xf0, 0x21,
    0x10, 0xa1, 0xf, 0xf9, 0x14, 0x8, 0x32, 0x5e,
    0xe, 0xa2, 0xac, 0x39, 0xa2, 0x84, 0x3e, 0x8c,
    0x1f, 0xc2, 0x81, 0x21, 0x50, 0x0,

    /* U+003A ":" */
    0x10, 0x58, 0x13, 0x83, 0x20, 0xb0, 0x20,

    /* U+003B ";" */
    0x10, 0x58, 0x13, 0x83, 0x48, 0xc0, 0x51, 0x0,

    /* U+003C "<" */
    0xf, 0xfe, 0xd, 0xa1, 0x5a, 0xc7, 0x9b, 0x84,
    0x74, 0x39, 0x90, 0x9e, 0x6d, 0x9, 0xe6, 0x43,
    0x36, 0x80,

    /* U+003D "=" */
    0x2b, 0xc2, 0xff, 0x7f, 0x90, 0xfc, 0xff, 0x95,
    0x5e, 0x40,

    /* U+003E ">" */
    0xf, 0xcf, 0x7, 0x2d, 0xe4, 0x2b, 0x8b, 0x42,
    0x74, 0x39, 0xd1, 0x2e, 0x2c, 0x5b, 0xc8, 0x1e,
    0xe,

    /* U+003F "?" */
    0x1f, 0x91, 0x82, 0x98, 0xf4, 0x6c, 0x4, 0x12,
    0x8, 0xc2, 0x5c, 0x14, 0xc1, 0x26, 0x19, 0xd0,
    0xe4, 0x3a, 0x88, 0x6c, 0x30,

    /* U+0040 "@" */
    0xe, 0xbf, 0x21, 0xf3, 0xaa, 0x8d, 0x87, 0x51,
    0xe5, 0x59, 0x84, 0xaa, 0x7, 0xb3, 0x4, 0x25,
    0xea, 0x6c, 0x1a, 0x24, 0xa, 0x2, 0x48, 0x89,
    0xf0, 0x64, 0x32, 0x21, 0x21, 0x90, 0xfe, 0x43,
    0x21, 0x22, 0x4, 0x32, 0x22, 0x27, 0xa0, 0x71,
    0xc, 0x48, 0x1d, 0x68, 0x11, 0x97, 0xa2, 0xf2,
    0x16, 0x70, 0x1b, 0xf, 0xb5, 0x7a, 0x50, 0x7e,
    0xbd, 0x7a, 0xc,

    /* U+0041 "A" */
    0xe, 0x7c, 0x87, 0xf6, 0xc, 0x3f, 0x90, 0x21,
    0xfa, 0x14, 0x41, 0xf2, 0x78, 0x43, 0xc8, 0x14,
    0x4, 0x3a, 0x10, 0x26, 0x1f, 0x40, 0xc4, 0x34,
    0xf, 0xa0, 0x41, 0x21, 0xf9, 0x2, 0xf, 0xf0,
    0x12, 0x20, 0xf2, 0x40,

    /* U+0042 "B" */
    0xbf, 0xd0, 0x7f, 0x30, 0x4f, 0xd0, 0x87, 0xc8,
    0x7f, 0x21, 0xcf, 0xd1, 0x87, 0xf4, 0x13, 0xf4,
    0x28, 0x3c, 0xa3, 0xf, 0x90, 0xcf, 0xe0, 0x41,
    0xf3, 0x80,

    /* U+0043 "C" */
    0xd, 0x7d, 0x6, 0xb4, 0x27, 0x45, 0xf, 0xc8,
    0x50, 0xc1, 0x5a, 0x81, 0x7, 0xf2, 0x1f, 0xe4,
    0x3f, 0xf8, 0xe8, 0x20, 0xfd, 0xc, 0x6, 0xd1,
    0x43, 0xe9, 0x10, 0x51, 0x9, 0xc0,

    /* U+0044 "D" */
    0xbf, 0xc8, 0x7f, 0xac, 0x33, 0xf4, 0xc, 0x3e,
    0x70, 0x21, 0xf9, 0x30, 0xfd, 0x88, 0x7f, 0xf1,
    0xf1, 0xf, 0xc9, 0x87, 0x9c, 0x8, 0x1f, 0xa0,
    0x61, 0xfa, 0xc0,

    /* U+0045 "E" */
    0xbf, 0xe8, 0x3f, 0xe7, 0xfa, 0xf, 0xfe, 0x43,
    0xfc, 0x1f, 0xfc, 0x7, 0xf8, 0x3f, 0xf9, 0x2f,
    0xf4, 0x1f, 0x90,

    /* U+0046 "F" */
    0xbf, 0xe0, 0xff, 0xe0, 0x3f, 0xc1, 0xff, 0xc9,
    0x7f, 0x41, 0xff, 0xc0, 0x7f, 0x41, 0xff, 0xd9,

    /* U+0047 "G" */
    0xd, 0x7d, 0x21, 0x3a, 0x13, 0x41, 0x87, 0xe8,
    0xc8, 0x60, 0x9d, 0x40, 0x83, 0xf9, 0xf, 0xfe,
    0x2f, 0x80, 0x87, 0xe4, 0x10, 0x7e, 0x86, 0xa,
    0x9, 0x87, 0xe4, 0x40, 0xe8, 0x4d, 0x0,

    /* U+0048 "H" */
    0xb8, 0x3b, 0xc8, 0x7f, 0xf8, 0x9f, 0xe0, 0xff,
    0xe2, 0x3f, 0xc1, 0xff, 0xe3,

    /* U+0049 "I" */
    0xb8, 0x3f, 0xfa, 0xa0,

    /* U+004A "J" */
    0x7, 0xf8, 0x3f, 0xdf, 0x83, 0xff, 0xcf, 0x69,
    0x4, 0x96, 0x91, 0xa1, 0x48,

    /* U+004B "K" */
    0xb8, 0x37, 0xa0, 0xfa, 0x4, 0x1e, 0x93, 0xf,
    0x28, 0xc3, 0xcc, 0x41, 0xf4, 0x4, 0x3c, 0x85,
    0x7, 0xcc, 0x28, 0x3d, 0x28, 0x83, 0x90, 0x40,
    0x83, 0xf6, 0x28, 0x3f, 0x24, 0x0,

    /* U+004C "L" */
    0xb8, 0x3f, 0xff, 0xe1, 0x9f, 0xc8, 0x7e,

    /* U+004D "M" */
    0xbc, 0x1e, 0x7c, 0x85, 0x7, 0x41, 0xe4, 0x32,
    0x1f, 0x90, 0xb0, 0xf2, 0x41, 0x22, 0x1b, 0x44,
    0x88, 0x3d, 0x90, 0x88, 0x79, 0x6, 0x21, 0xfa,
    0xa, 0xf, 0xc8, 0x10, 0xff, 0x44, 0x1f, 0xe7,
    0xf, 0x0,

    /* U+004E "N" */
    0xb8, 0x3b, 0xc8, 0x14, 0x1f, 0xe8, 0x3f, 0xec,
    0x3f, 0x20, 0x83, 0xee, 0x14, 0x1f, 0x28, 0x83,
    0xf4, 0x8, 0x3f, 0x62, 0x1f, 0xc8, 0x7f, 0xa0,
    0xff, 0xb0, 0x80,

    /* U+004F "O" */
    0xd, 0x7d, 0x7, 0xad, 0x9, 0xd0, 0x94, 0x3f,
    0x24, 0x82, 0x18, 0x29, 0x21, 0x4, 0x1d, 0x7,
    0x21, 0xfc, 0x87, 0xff, 0xd, 0xf, 0xe5, 0x2,
    0xe, 0x83, 0x43, 0x5, 0x24, 0x6, 0x1f, 0x92,
    0x42, 0x74, 0x27, 0x40,

    /* U+0050 "P" */
    0xbf, 0xc8, 0x7f, 0x50, 0x27, 0xe8, 0x43, 0xe4,
    0x8, 0x7c, 0x87, 0xf2, 0x1f, 0xa0, 0x20, 0x7e,
    0x48, 0x3f, 0x48, 0x4f, 0xe4, 0x3f, 0xf9, 0x40,

    /* U+0051 "Q" */
    0xd, 0x7d, 0x7, 0xd6, 0x84, 0xe8, 0x65, 0xf,
    0xc9, 0x21, 0x43, 0x5, 0x24, 0x4, 0x10, 0x74,
    0x1e, 0x43, 0xf9, 0xf, 0xfe, 0x2a, 0x1f, 0xc8,
    0x82, 0xe, 0x83, 0xa1, 0x82, 0x92, 0x9, 0x43,
    0xf2, 0x48, 0x6b, 0x43, 0x68, 0x7d, 0x70, 0x11,
    0x41, 0xf2, 0x8b, 0xa0, 0x7e, 0xa0, 0x1c,

    /* U+0052 "R" */
    0xbf, 0xc8, 0x7f, 0x50, 0x27, 0xe8, 0x50, 0x79,
    0x46, 0x1f, 0x61, 0xfd, 0x98, 0x79, 0x42, 0x7,
    0xe8, 0x43, 0xf3, 0x4, 0xfc, 0x21, 0xf9, 0x30,
    0xfa, 0x2,

    /* U+0053 "S" */
    0xa, 0xfa, 0x9, 0xd0, 0x9c, 0x10, 0xfa, 0x50,
    0x7c, 0xd0, 0x8, 0xc1, 0xe8, 0xf, 0x90, 0xdc,
    0x15, 0x3, 0x3e, 0x44, 0x8, 0x68, 0xa, 0xb4,
    0x8, 0x14, 0xb, 0xd0, 0x83, 0x83, 0x50,

    /* U+0054 "T" */
    0xff, 0xe4, 0x3f, 0xdf, 0x40, 0xf9, 0xf, 0xff,
    0xf8, 0x7f, 0xf0, 0xc0,

    /* U+0055 "U" */
    0xf2, 0x1d, 0xe0, 0xff, 0xff, 0x84, 0x98, 0x64,
    0x2c, 0x60, 0x31, 0xa, 0x1f, 0x40, 0x41, 0x40,
    0xd6, 0x0,

    /* U+0056 "V" */
    0xf4, 0x1e, 0xf1, 0x8, 0x74, 0x22, 0x1f, 0x24,
    0x4, 0x82, 0x43, 0xb1, 0xb, 0x20, 0x90, 0x20,
    0x44, 0x32, 0x62, 0x21, 0xd0, 0x99, 0x87, 0xe5,
    0x8, 0x7a, 0x21, 0xf, 0x90, 0xa0, 0xfc, 0x87,
    0xc0,

    /* U+0057 "W" */
    0xf2, 0x1a, 0xe0, 0xcf, 0x26, 0x19, 0x10, 0xd9,
    0xc2, 0x1f, 0x21, 0x22, 0x12, 0x4, 0x4c, 0x3e,
    0x4c, 0x11, 0x8, 0x21, 0x6, 0x21, 0xfc, 0x90,
    0x10, 0x92, 0x11, 0xf, 0x91, 0xc4, 0xcd, 0x10,
    0xd9, 0xa1, 0x23, 0x98, 0x64, 0x44, 0x24, 0x44,
    0x39, 0x6, 0x16, 0x4, 0x3d, 0x81, 0x9, 0x6,
    0x10,

    /* U+0058 "X" */
    0x3c, 0x86, 0xf2, 0x24, 0x16, 0x28, 0x81, 0x10,
    0x20, 0xa1, 0x62, 0xc, 0xa2, 0x14, 0x1d, 0x5,
    0x7, 0xf9, 0xf, 0x61, 0x41, 0xd0, 0x30, 0x41,
    0x92, 0x21, 0x40, 0xc5, 0xa, 0x21, 0x4, 0x14,
    0x8,

    /* U+0059 "Y" */
    0x3c, 0x87, 0x78, 0x11, 0x6, 0x84, 0xa, 0x20,
    0x92, 0xa, 0x10, 0x42, 0x1c, 0x90, 0x90, 0x74,
    0x38, 0x87, 0xc8, 0x50, 0x7d, 0x1, 0xf, 0xfb,
    0xf, 0xfe, 0xe0,

    /* U+005A "Z" */
    0x3f, 0xf8, 0x3f, 0xf8, 0x3f, 0xd0, 0x20, 0xfa,
    0x14, 0x1e, 0xc6, 0xf, 0x40, 0x83, 0xca, 0x30,
    0xfa, 0x20, 0xfb, 0x14, 0x1e, 0x81, 0x7, 0x94,
    0xf, 0xf0, 0x7f, 0xf0, 0x0,

    /* U+005B "[" */
    0xbe, 0xc, 0x85, 0x40, 0xff, 0xf4, 0xd9, 0xac,
    0x0,

    /* U+005C "\\" */
    0x20, 0xf9, 0x83, 0xe4, 0x3d, 0x8, 0x72, 0x61,
    0xf2, 0x1e, 0x84, 0x39, 0x30, 0xf9, 0xf, 0x42,
    0x1c, 0x98, 0x7c, 0x87, 0xa1, 0xe, 0x4c, 0x3e,
    0x43, 0xc8, 0x80,

    /* U+005D "]" */
    0xfc, 0x28, 0x2a, 0x7, 0xff, 0xa7, 0xc1, 0x2e,
    0x0,

    /* U+0061 "a" */
    0x5, 0xf4, 0x14, 0x84, 0xe0, 0xa7, 0xc0, 0x40,
    0x84, 0x84, 0xfe, 0x42, 0x8a, 0x82, 0x45, 0xc1,
    0x23, 0x4c, 0x34, 0x2e, 0x0,

    /* U+0062 "b" */
    0xb4, 0x3f, 0xfa, 0x4f, 0xc8, 0x6a, 0x5, 0x21,
    0xaf, 0x24, 0x12, 0x81, 0x1, 0x6, 0x1f, 0xd8,
    0x7f, 0x28, 0x10, 0x10, 0xaf, 0x24, 0x15, 0x2,
    0x90,

    /* U+0063 "c" */
    0x3, 0xf4, 0x13, 0x4, 0xe0, 0x8b, 0xd2, 0x20,
    0x40, 0xc1, 0x21, 0xf9, 0xf, 0x20, 0x40, 0xc0,
    0x8b, 0xd2, 0x86, 0x9, 0xd0,

    /* U+0064 "d" */
    0xf, 0xae, 0xf, 0xfe, 0x53, 0xf2, 0x1a, 0x81,
    0x48, 0x48, 0xfa, 0x9, 0x4, 0x4, 0x39, 0xc,
    0x86, 0x43, 0xe4, 0x8, 0x14, 0x12, 0x5e, 0x83,
    0x50, 0x29, 0x0,

    /* U+0065 "e" */
    0x3, 0xf4, 0x19, 0x82, 0x70, 0xa3, 0xe8, 0x84,
    0x39, 0x10, 0xdf, 0x83, 0xd5, 0xe1, 0x9, 0x61,
    0x4, 0x5f, 0x48, 0x18, 0x26, 0x40,

    /* U+0066 "f" */
    0x3, 0xf2, 0x8, 0x39, 0x7, 0x95, 0x3, 0xc0,
    0x40, 0xa1, 0xc1, 0x40, 0xff, 0xef, 0x80,

    /* U+0067 "g" */
    0x5, 0xf1, 0xe0, 0x48, 0x98, 0x64, 0xed, 0x9,
    0x10, 0xa0, 0xff, 0xe0, 0xa2, 0x14, 0x19, 0x3e,
    0x43, 0x48, 0x58, 0x75, 0xf0, 0x72, 0x82, 0x83,
    0x53, 0xe4, 0xc1, 0xa1, 0x38, 0x0,

    /* U+0068 "h" */
    0xb4, 0x3f, 0xf9, 0xef, 0xc8, 0x54, 0xa, 0xd,
    0x78, 0x10, 0x14, 0x8, 0x36, 0x1f, 0xfd, 0xe0,

    /* U+0069 "i" */
    0x73, 0x1a, 0x34, 0x43, 0xff, 0x98,

    /* U+006A "j" */
    0xa, 0xd0, 0x93, 0xb, 0x60, 0xa5, 0x7, 0xff,
    0x9d, 0xb, 0xc0, 0x43, 0x60,

    /* U+006B "k" */
    0xb4, 0x3f, 0xfa, 0x37, 0x83, 0x94, 0x61, 0x98,
    0xc3, 0x50, 0x83, 0xf4, 0x1e, 0x80, 0x86, 0x54,
    0x41, 0xb1, 0x4, 0x1e, 0xc5, 0x0,

    /* U+006C "l" */
    0xb4, 0x3f, 0xfa, 0xa0,

    /* U+006D "m" */
    0xb5, 0x7c, 0x7, 0xe4, 0x2a, 0x5, 0xb0, 0x50,
    0x6b, 0x81, 0x4e, 0x2, 0x5, 0xa, 0x14, 0x28,
    0xc1, 0x87, 0xf6, 0x1f, 0xff, 0x20,

    /* U+006E "n" */
    0xb5, 0x7c, 0x85, 0x40, 0xa0, 0xd7, 0x1, 0x2,
    0x85, 0x18, 0x30, 0xb0, 0xff, 0xed, 0x0,

    /* U+006F "o" */
    0x3, 0x7c, 0x84, 0xc8, 0x52, 0x8, 0xbd, 0x10,
    0x81, 0x2, 0x4, 0x8, 0x64, 0xc0, 0x86, 0x4d,
    0x2, 0x4, 0x9, 0x17, 0xa2, 0x3, 0x6, 0x90,

    /* U+0070 "p" */
    0xb5, 0x7c, 0x86, 0xa0, 0x52, 0x1a, 0xf2, 0x41,
    0x28, 0x10, 0x10, 0x61, 0xfd, 0x87, 0xf2, 0x81,
    0x1, 0xa, 0xf2, 0x41, 0x50, 0x29, 0xc, 0xfc,
    0x87, 0xff, 0x28,

    /* U+0071 "q" */
    0x3, 0xf3, 0x71, 0x40, 0xa4, 0x24, 0xbd, 0x4,
    0x81, 0x2, 0x83, 0x21, 0xfc, 0x87, 0xc8, 0x10,
    0x28, 0x24, 0xbd, 0x6, 0xa0, 0x52, 0x19, 0xf9,
    0xf, 0xfe, 0x58,

    /* U+0072 "r" */
    0xb5, 0x68, 0x28, 0x1c, 0xe8, 0x18, 0x36, 0x1f,
    0xfc, 0xf0,

    /* U+0073 "s" */
    0x5, 0xf2, 0xd, 0xa, 0xd, 0xf8, 0x34, 0x86,
    0x86, 0xd0, 0x3c, 0x90, 0x11, 0x82, 0xa7, 0x61,
    0x50, 0x47, 0x0,

    /* U+0074 "t" */
    0x1e, 0xf, 0xf5, 0x7, 0xc6, 0x81, 0x43, 0x8d,
    0x3, 0xff, 0x9a, 0x86, 0x41, 0xe0, 0xa0, 0x20,

    /* U+0075 "u" */
    0xf0, 0x6f, 0x7, 0xff, 0x92, 0x4, 0x14, 0x3e,
    0x42, 0x50, 0x1c, 0x20,

    /* U+0076 "v" */
    0x3c, 0x85, 0x71, 0x18, 0x49, 0x8, 0x87, 0xe4,
    0x48, 0x82, 0xcc, 0x44, 0x24, 0x40, 0x87, 0x26,
    0x61, 0xd8, 0x48, 0x72, 0x4, 0x20,

    /* U+0077 "w" */
    0x3c, 0x85, 0xe8, 0x2b, 0x48, 0xc3, 0x90, 0x91,
    0x11, 0x4, 0x1c, 0x88, 0x7c, 0x90, 0x99, 0x85,
    0x10, 0x14, 0x62, 0x21, 0x22, 0x8c, 0x8, 0x10,
    0xfa, 0x12, 0x33, 0xe, 0x80, 0x81, 0x9, 0xe,
    0x41, 0x87, 0x21, 0x0,

    /* U+0078 "x" */
    0x7c, 0x17, 0x96, 0x22, 0x14, 0x42, 0xc4, 0x14,
    0x42, 0x19, 0xa, 0xd, 0x5, 0x6, 0x48, 0x50,
    0x32, 0x62, 0x20, 0x22, 0x8,

    /* U+0079 "y" */
    0x3c, 0x19, 0xe2, 0x20, 0xa2, 0x11, 0xf, 0xc8,
    0x91, 0x5, 0x90, 0x88, 0x48, 0x11, 0xe, 0x88,
    0xc3, 0x90, 0x90, 0xf2, 0x41, 0xf2, 0x21, 0xaf,
    0x8, 0x7e, 0x60, 0xc0,

    /* U+007A "z" */
    0x3f, 0xe0, 0xff, 0xbf, 0x3, 0xe, 0xc8, 0x3b,
    0x24, 0x34, 0x28, 0x32, 0x88, 0x3a, 0x7, 0xe1,
    0xf, 0xc0,

    /* U+007B "{" */
    0x5, 0xe0, 0x90, 0xc8, 0xe1, 0xff, 0xc7, 0x63,
    0xe, 0x40, 0xc4, 0x1f, 0xfc, 0x94, 0x43, 0xd8,
    0x52, 0x80,

    /* U+007C "|" */
    0x12, 0x81, 0xff, 0xdf,

    /* U+007D "}" */
    0x3c, 0x87, 0x41, 0x61, 0xe4, 0x3f, 0xf8, 0xb9,
    0xa0, 0x43, 0xa2, 0x43, 0x21, 0xff, 0xc3, 0x43,
    0x61, 0xca, 0xc0,

    /* U+007E "~" */
    0x24, 0x63, 0x6e, 0x40, 0xe9, 0x0,

    /* U+2026 "…" */
    0xf, 0xfb, 0x8f, 0x16, 0x87, 0xf2
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 77, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 98, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 186, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 253, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 171, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 121, .adv_w = 56, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 124, .adv_w = 83, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 143, .adv_w = 89, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 159, .adv_w = 91, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 169, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 184, .adv_w = 57, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 188, .adv_w = 58, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 86, .box_w = 8, .box_h = 16, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 218, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 158, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 58, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 57, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 485, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 503, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 513, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 530, .adv_w = 115, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 245, .box_w = 15, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 610, .adv_w = 191, .box_w = 13, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 182, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 178, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 198, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 169, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 149, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 191, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 202, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 78, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 130, .box_w = 8, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 186, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 236, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 202, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 923, .adv_w = 207, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 959, .adv_w = 173, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 209, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1030, .adv_w = 185, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1056, .adv_w = 161, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1087, .adv_w = 151, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1099, .adv_w = 195, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1117, .adv_w = 179, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1150, .adv_w = 268, .box_w = 17, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1199, .adv_w = 180, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1232, .adv_w = 166, .box_w = 12, .box_h = 12, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1259, .adv_w = 171, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1288, .adv_w = 90, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1297, .adv_w = 133, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1324, .adv_w = 118, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1333, .adv_w = 151, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1354, .adv_w = 174, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1379, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1400, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1427, .adv_w = 152, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 91, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1464, .adv_w = 164, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1494, .adv_w = 172, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1510, .adv_w = 74, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1516, .adv_w = 76, .box_w = 6, .box_h = 15, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 1529, .adv_w = 155, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1551, .adv_w = 77, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1555, .adv_w = 266, .box_w = 15, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1577, .adv_w = 170, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1592, .adv_w = 161, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1616, .adv_w = 174, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1643, .adv_w = 175, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1670, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1680, .adv_w = 123, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 106, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1715, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1727, .adv_w = 137, .box_w = 10, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1749, .adv_w = 232, .box_w = 16, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1785, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1806, .adv_w = 139, .box_w = 10, .box_h = 12, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 1834, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1852, .adv_w = 86, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1870, .adv_w = 71, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1874, .adv_w = 102, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1893, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1899, .adv_w = 161, .box_w = 10, .box_h = 3, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 0, 1, 2, 0, 3, 4, 5,
    6, 7, 8, 9, 10
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 13, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    },
    {
        .range_start = 46, .range_length = 48, .glyph_id_start = 12,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 30, .glyph_id_start = 60,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8230, .range_length = 1, .glyph_id_start = 90,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 0, 1, 2,
    0, 3, 0, 0, 0, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 5,
    6, 7, 8, 0, 9, 0, 0, 0,
    10, 11, 12, 0, 0, 8, 13, 8,
    14, 15, 16, 17, 18, 19, 20, 21,
    0, 22, 0, 0, 23, 24, 25, 26,
    27, 28, 29, 30, 0, 29, 31, 26,
    30, 30, 24, 24, 32, 33, 34, 35,
    36, 37, 37, 31, 38, 39, 0, 0,
    0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    4, 5, 4, 4, 4, 5, 4, 4,
    6, 4, 4, 4, 4, 7, 4, 5,
    4, 8, 9, 10, 11, 11, 0, 12,
    0, 0, 13, 0, 14, 15, 16, 16,
    16, 17, 16, 15, 0, 0, 15, 15,
    18, 18, 16, 19, 16, 18, 20, 21,
    21, 22, 22, 23, 22, 24, 0, 0,
    25, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, -15, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 8, 0, 8,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -6, -5, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, -5, -1, -18, -5, -13, -13,
    -9, 0, 0, -6, 0, 0, 0, 0,
    -6, -7, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, -4, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, -5, 0, -6, -7, -6, 0, -4,
    0, -3, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -3, 0, 0,
    0, -8, -8, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, -5, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, -6, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -14,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, -12, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, -2,
    -2, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    -14, -18, 0, -10, -4, -10, 0, 0,
    0, 0, 0, 0, -2, -13, -18, 0,
    -8, 0, -4, -8, -8, 0, -7, 0,
    0, -4, -5, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, -2, -4, -13, 0, -3, 0, -1,
    0, 0, 0, 0, 0, 0, -13, 0,
    -14, 0, -7, -4, -5, -7, -2, -5,
    -5, 0, -5, -4, -13, 0, -3, 0,
    -1, 0, 0, 0, 0, 0, 0, -13,
    0, -14, 0, -7, -4, -5, -7, -2,
    -5, -5, 0, 0, 0, 0, 0, -4,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -13, 0,
    -7, 0, -1, 0, 0, 0, 0, 0,
    0, -13, 0, -14, 0, -7, -4, -5,
    -7, -2, -5, -5, 0, 0, 0, 0,
    0, -4, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, -2, 0, 0, -8, 0,
    -10, -10, -2, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -2, -7, 0,
    0, -6, 0, 0, -10, 0, 0, -18,
    0, -14, -14, -2, 0, 0, 0, -2,
    0, 0, 0, 0, -5, -8, -1, -2,
    0, 0, 0, 0, -4, 0, -4, 0,
    0, 0, -5, -5, 0, -5, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, 0, -10,
    0, 0, -18, 0, -14, -14, -3, 0,
    0, 0, -2, 0, 0, 0, 0, -5,
    -8, -1, -9, 0, 2, -3, 8, 7,
    -5, 7, 0, 24, 2, 11, 11, 0,
    -7, 4, -3, 1, 0, 0, 0, 3,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, -2, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -2, 0, 0, -8, 0, -10,
    -10, -8, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, -2, -1, 0, 0,
    0, 0, -3, 0, -3, 0, 0, -5,
    -5, -5, 0, -6, 0, -7, 0, 0,
    0, -3, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, -4, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, -4, -4, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -5, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -3,
    0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, -7, -7, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -2, -4, 0, -8, 0, -1, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, -7, 0,
    -1, -1, -1, 0, -8, 0, -2, -2,
    0, -4, 0, -5, 0, 1, 0, -2,
    0, 0, -1, 0, 0, 0, -4, -7,
    0, -1, -1, -1, 0, -8, 0, -2,
    -2, 0, -4, 0, -5, 0, 1, 0,
    -2, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -5, 0, -2, 0, -1, 0, -2,
    0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 39,
    .right_class_cnt     = 25,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 4,
    .bpp = 2,
    .kern_classes = 1,
    .bitmap_format = 1,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_montserratMedium_18 = {
#else
lv_font_t lv_font_montserratMedium_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if LV_FONT_MONTSERRATMEDIUM_18*/

