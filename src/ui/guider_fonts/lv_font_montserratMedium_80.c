/*******************************************************************************
 * Size: 80 px
 * Bpp: 2
 * Opts: --bpp 2 --size 80 --font Montserrat-Medium.ttf --symbols 1234567890 --format lvgl -o lv_font_montserratMedium_80.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_FONT_MONTSERRATMEDIUM_80
#define LV_FONT_MONTSERRATMEDIUM_80 1
#endif

#if LV_FONT_MONTSERRATMEDIUM_80

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0xf, 0xfe, 0x23, 0x7f, 0xd4, 0x43, 0xff, 0xa1,
    0x7a, 0x43, 0xe5, 0x5c, 0x87, 0xff, 0x2e, 0xd0,
    0xff, 0xe1, 0xb6, 0x87, 0xff, 0x1d, 0xd0, 0xff,
    0xe4, 0x50, 0x3f, 0xf8, 0xb4, 0xf, 0xfe, 0x5b,
    0x87, 0xff, 0xe, 0x43, 0xff, 0x9d, 0x87, 0xff,
    0x5, 0x41, 0xff, 0xd0, 0xc3, 0xfe, 0x60, 0xff,
    0xe9, 0x41, 0xfe, 0x83, 0xff, 0x80, 0xd3, 0xa2,
    0x1f, 0xfc, 0x5, 0x7, 0xe8, 0x3f, 0xe7, 0x94,
    0x2a, 0xe0, 0xff, 0xa0, 0xfc, 0x87, 0xf9, 0x83,
    0xf9, 0xc3, 0xfe, 0x43, 0xd0, 0x7f, 0x98, 0x3f,
    0xf8, 0x18, 0x7f, 0xa0, 0xf2, 0x1f, 0xe8, 0x3f,
    0xf8, 0x48, 0x7f, 0x90, 0xc8, 0x7f, 0xa0, 0xff,
    0xe1, 0xc1, 0xfe, 0x83, 0x41, 0xfe, 0x43, 0xff,
    0x88, 0x87, 0xff, 0x31, 0xf, 0xfe, 0x2c, 0x1f,
    0xe4, 0x8, 0x7f, 0xa0, 0xff, 0xe8, 0x60, 0xc3,
    0xff, 0xa2, 0x87, 0xf2, 0x4, 0x3f, 0x90, 0xff,
    0xe3, 0xe1, 0xff, 0xde, 0x43, 0xfc, 0x87, 0xfd,
    0x87, 0xff, 0x4d, 0xf, 0xfe, 0xee, 0x1f, 0xf2,
    0x1f, 0xff, 0x34, 0x3f, 0x9c, 0x3f, 0xff, 0xe1,
    0xff, 0xff, 0xf, 0xff, 0xf8, 0x7f, 0xff, 0xc3,
    0xff, 0xbf, 0x87, 0xff, 0xf9, 0xf, 0xe4, 0x3f,
    0xe4, 0x3f, 0xfa, 0x68, 0x7f, 0xf7, 0x70, 0xff,
    0xb0, 0xff, 0xf9, 0x21, 0xfe, 0x44, 0x3f, 0x90,
    0xff, 0xe3, 0xe1, 0xff, 0xc0, 0xc3, 0xff, 0xa2,
    0x87, 0xf2, 0x4, 0x3f, 0xd0, 0x7f, 0xf4, 0x30,
    0xff, 0xe0, 0xa1, 0xff, 0xc5, 0x83, 0xfc, 0x85,
    0x7, 0xf9, 0xf, 0xfe, 0x22, 0x1f, 0xfc, 0x24,
    0x3f, 0xd0, 0x7f, 0xf0, 0xe0, 0xff, 0x41, 0xc8,
    0x7f, 0xa0, 0xff, 0xe1, 0x21, 0xfe, 0x43, 0xa0,
    0xff, 0x30, 0x7f, 0xf0, 0x30, 0xff, 0x41, 0xf2,
    0x1f, 0xe6, 0xf, 0xe7, 0xf, 0xf9, 0xf, 0xa0,
    0xff, 0x9e, 0x50, 0x1b, 0x83, 0xfe, 0x83, 0xfa,
    0xf, 0xfe, 0x3, 0x4f, 0x48, 0x7f, 0xf0, 0x14,
    0x1f, 0xcc, 0x1f, 0xfd, 0x28, 0x3f, 0xe5, 0x7,
    0xff, 0x43, 0xf, 0xfe, 0xc, 0x87, 0xff, 0x3b,
    0xf, 0xfe, 0x1d, 0x3, 0xff, 0x96, 0xe1, 0xff,
    0xc5, 0x74, 0x3f, 0xf9, 0x1c, 0x1f, 0xfc, 0x8b,
    0x43, 0xff, 0x86, 0xd8, 0x7f, 0xf3, 0x2f, 0x48,
    0x7c, 0xab, 0x90, 0xff, 0xe0, 0x0,

    /* U+0031 "1" */
    0xff, 0xfe, 0x54, 0x1f, 0xff, 0xf0, 0xff, 0xff,
    0x87, 0xff, 0x5a, 0xbf, 0xf8, 0x1, 0xff, 0x2f,
    0xff, 0x0, 0x3f, 0xff, 0xe1, 0xff, 0xff, 0xf,
    0xff, 0xf8, 0x7f, 0xff, 0xc3, 0xff, 0xfe, 0x1f,
    0xff, 0xf0, 0xff, 0xff, 0x87, 0xff, 0xfc, 0x3f,
    0xff, 0xe1, 0xff, 0xff, 0xf, 0xff, 0xf8, 0x7f,
    0xff, 0xc3, 0xff, 0xfe, 0x1f, 0xff, 0xb0,

    /* U+0032 "2" */
    0xf, 0xfe, 0x23, 0x4f, 0xfa, 0x88, 0x7f, 0xf3,
    0xdb, 0xd2, 0x83, 0xe5, 0x5e, 0x43, 0xff, 0x95,
    0x72, 0x1f, 0xfc, 0x5b, 0x83, 0xff, 0x8d, 0x68,
    0x7f, 0xf2, 0x9d, 0xf, 0xfe, 0x15, 0xa1, 0xff,
    0xce, 0xa0, 0x7f, 0xce, 0x87, 0xff, 0x45, 0x83,
    0xfb, 0x83, 0xff, 0xa8, 0xc1, 0xe7, 0xf, 0xfe,
    0xba, 0x1e, 0x83, 0xff, 0xb3, 0x87, 0x41, 0xff,
    0xc3, 0x55, 0x65, 0x7, 0xff, 0x21, 0xf, 0xfe,
    0x3, 0x74, 0x5d, 0x4e, 0xf, 0xfe, 0xc, 0x1d,
    0x7, 0xf5, 0xc8, 0x7f, 0x9c, 0x3f, 0xf8, 0x8,
    0x72, 0x1f, 0x5a, 0x1f, 0xfc, 0x3c, 0x3f, 0xf8,
    0xd0, 0x67, 0x43, 0xff, 0x8c, 0x87, 0xff, 0x15,
    0x40, 0xa0, 0x7f, 0xf2, 0x30, 0xff, 0xe3, 0x46,
    0x87, 0xff, 0x25, 0xf, 0xfe, 0x3e, 0x1f, 0xff,
    0x74, 0x3f, 0xc8, 0x7f, 0xf5, 0x20, 0xff, 0x41,
    0xff, 0xff, 0xc3, 0xfd, 0x7, 0xff, 0x4d, 0xf,
    0xf9, 0xf, 0xfe, 0x9c, 0x1f, 0xe8, 0x3f, 0xfa,
    0x78, 0x7f, 0x94, 0x1f, 0xfd, 0x28, 0x3f, 0xe8,
    0x3f, 0xfa, 0x52, 0x1f, 0xe8, 0x3f, 0xfa, 0x52,
    0x1f, 0xe5, 0x7, 0xff, 0x46, 0x43, 0xfe, 0x83,
    0xff, 0xa3, 0x21, 0xff, 0x61, 0xff, 0xd1, 0x90,
    0xff, 0xb0, 0xff, 0xe8, 0xc8, 0x7f, 0xd0, 0x7f,
    0xf4, 0x64, 0x3f, 0xe9, 0xf, 0xfe, 0x84, 0x87,
    0xfd, 0x21, 0xff, 0xd0, 0x50, 0x7f, 0xd2, 0x1f,
    0xfd, 0x6, 0xf, 0xfa, 0x43, 0xff, 0xa0, 0xc1,
    0xff, 0x48, 0x7f, 0xf4, 0x18, 0x3f, 0xe9, 0xf,
    0xfe, 0x83, 0x7, 0xfd, 0x21, 0xff, 0xd0, 0x60,
    0xff, 0xa4, 0x3f, 0xfa, 0xc, 0x1f, 0xf4, 0x87,
    0xff, 0x41, 0x83, 0xfe, 0xd0, 0xff, 0xe8, 0x30,
    0x7f, 0xd8, 0x7f, 0xf4, 0x58, 0x3f, 0xec, 0x3f,
    0xfa, 0x2c, 0x1f, 0xf6, 0x1f, 0xfd, 0x16, 0xf,
    0xfb, 0xf, 0xfe, 0x8b, 0x7, 0xfd, 0x87, 0xff,
    0x45, 0x83, 0xfe, 0x5f, 0xfe, 0x78, 0x4c, 0x1f,
    0xfc, 0x6, 0xbf, 0xf9, 0xe0, 0x83, 0xff, 0xfe,
    0x1f, 0xff, 0xf0, 0xff, 0xff, 0x87, 0xff, 0xfc,
    0x3f, 0xfc, 0xa0,

    /* U+0033 "3" */
    0xb, 0xff, 0xfb, 0x30, 0x7f, 0xf9, 0x90, 0xff,
    0xff, 0x87, 0xff, 0xfc, 0x3f, 0xff, 0xe1, 0xff,
    0xd2, 0x60, 0xff, 0xee, 0xb0, 0x7d, 0x5f, 0xfc,
    0xc0, 0xff, 0x30, 0x7f, 0x2f, 0xff, 0x2a, 0xf,
    0xea, 0x7, 0xff, 0x4f, 0xf, 0xe9, 0xf, 0xfe,
    0x9e, 0x1f, 0xd2, 0x1f, 0xfd, 0x3c, 0x3f, 0xa4,
    0x3f, 0xfa, 0x78, 0x7f, 0x48, 0x7f, 0xf4, 0x9c,
    0x3f, 0xb4, 0x3f, 0xfa, 0x4c, 0x1f, 0xd8, 0x7f,
    0xf4, 0xd8, 0x3f, 0xb0, 0xff, 0xe9, 0xb0, 0x7f,
    0x61, 0xff, 0xd3, 0xa0, 0x7f, 0x61, 0xff, 0xd3,
    0x90, 0xfe, 0xc3, 0xff, 0xa7, 0x21, 0xf9, 0xc3,
    0xff, 0xa7, 0x21, 0xfd, 0x7, 0xff, 0x4e, 0x43,
    0xfd, 0xf4, 0xa0, 0xff, 0xe7, 0x21, 0xff, 0xc2,
    0x69, 0xe8, 0x3f, 0xfb, 0xef, 0x21, 0xff, 0xde,
    0x68, 0x1f, 0xfd, 0xf7, 0x43, 0xff, 0xbf, 0x21,
    0xff, 0xdf, 0x90, 0xff, 0xe1, 0xff, 0xff, 0x2,
    0x81, 0xff, 0xc2, 0x83, 0xff, 0x9e, 0xaf, 0x21,
    0xff, 0xc0, 0xc3, 0xff, 0xa5, 0x61, 0xff, 0xc0,
    0x43, 0xff, 0xa7, 0x87, 0xfd, 0x87, 0xff, 0x53,
    0xf, 0xf2, 0x1f, 0xfd, 0x54, 0x3f, 0xfb, 0xf8,
    0x7f, 0x90, 0xff, 0xea, 0x21, 0xff, 0xff, 0xf,
    0xff, 0x62, 0x1f, 0xfc, 0x35, 0x7, 0xff, 0x3b,
    0xf, 0xf2, 0x1a, 0xa0, 0xff, 0xe6, 0x28, 0x3f,
    0xf8, 0x48, 0x1d, 0xf, 0xfe, 0x54, 0x1f, 0xe4,
    0x34, 0x1a, 0x81, 0xff, 0xc8, 0xc3, 0xfe, 0xc2,
    0x43, 0xcf, 0x90, 0xff, 0xe1, 0xd8, 0x7f, 0xf0,
    0x10, 0xa0, 0xfe, 0xb9, 0xf, 0xe6, 0xd0, 0xff,
    0xe0, 0x41, 0x21, 0xff, 0xc0, 0x6f, 0xfe, 0x90,
    0xff, 0xe0, 0xa8, 0x28, 0x3f, 0xfb, 0x50, 0x48,
    0x7f, 0xf6, 0xb0, 0xcc, 0x1f, 0xfd, 0x8c, 0x3c,
    0xe8, 0x7f, 0xf5, 0x1c, 0x3f, 0xad, 0xf, 0xfe,
    0x8d, 0x3, 0xff, 0x81, 0x70, 0x7f, 0xf3, 0x5d,
    0xf, 0xfe, 0x1b, 0xe9, 0xf, 0xfe, 0x33, 0x70,
    0x7f, 0xf2, 0x1b, 0xd2, 0x83, 0xf2, 0xaf, 0x48,
    0x7f, 0xf0, 0x0,

    /* U+0034 "4" */
    0xf, 0xfe, 0x3f, 0xff, 0x90, 0xff, 0xeb, 0x21,
    0xfe, 0x43, 0xff, 0xad, 0x7, 0xf4, 0x1f, 0xfd,
    0x64, 0x3f, 0xc8, 0x7f, 0xf5, 0xa0, 0xfe, 0x83,
    0xff, 0xad, 0x7, 0xf9, 0xf, 0xfe, 0xb2, 0x1f,
    0xd0, 0x7f, 0xf5, 0xa0, 0xff, 0x21, 0xff, 0xd6,
    0x43, 0xfa, 0xf, 0xfe, 0xb4, 0x1f, 0xe4, 0x3f,
    0xfa, 0xc8, 0x7f, 0x61, 0xff, 0xd6, 0x83, 0xf9,
    0xf, 0xfe, 0xba, 0x1f, 0xd0, 0x7f, 0xf5, 0xb0,
    0xfe, 0x43, 0xff, 0xac, 0x87, 0xfa, 0xf, 0xfe,
    0xb4, 0x1f, 0xc8, 0x7f, 0xf5, 0x90, 0xff, 0x41,
    0xff, 0xd6, 0x83, 0xf9, 0xf, 0xfe, 0xb2, 0x1f,
    0xe8, 0x3f, 0xfa, 0xd0, 0x7f, 0x41, 0xff, 0xd6,
    0x83, 0xfc, 0x87, 0xe5, 0xfe, 0xf, 0xfe, 0x2a,
    0x1f, 0xd0, 0x7e, 0xaf, 0xf2, 0x1f, 0xfc, 0x38,
    0x3f, 0xc8, 0x7f, 0xf5, 0x90, 0xfe, 0x83, 0xff,
    0xad, 0x7, 0xf9, 0xf, 0xfe, 0xb2, 0x1f, 0xd0,
    0x7f, 0xf5, 0xa0, 0xff, 0x21, 0xff, 0xd5, 0x50,
    0x7f, 0x41, 0xff, 0xd6, 0x83, 0xf9, 0x41, 0xff,
    0xd5, 0x43, 0xfd, 0x7, 0xff, 0x5a, 0xf, 0xe4,
    0x3f, 0xfa, 0xc8, 0x7f, 0xa0, 0xff, 0xeb, 0x41,
    0xfc, 0x87, 0xff, 0x59, 0xf, 0xf6, 0x1f, 0xfc,
    0xcc, 0x3f, 0xa0, 0xff, 0x5f, 0xff, 0xc2, 0x43,
    0xf9, 0xff, 0x94, 0x1f, 0xff, 0xf0, 0xff, 0xff,
    0x87, 0xff, 0xfc, 0x3f, 0xff, 0xe1, 0xff, 0xf7,
    0x7f, 0xff, 0x9c, 0x87, 0xf5, 0xff, 0x21, 0xff,
    0xff, 0xf, 0xff, 0xf8, 0x7f, 0xff, 0xc3, 0xff,
    0xfe, 0x1f, 0xff, 0xf0, 0xff, 0xff, 0x87, 0xff,
    0xfc, 0x3f, 0xf9, 0xe0,

    /* U+0035 "5" */
    0xe, 0xff, 0xfe, 0xc0, 0x7f, 0xff, 0xc3, 0xff,
    0xfe, 0x1f, 0xff, 0xf0, 0xff, 0xff, 0x87, 0xff,
    0xea, 0xbf, 0xf9, 0xc1, 0xff, 0xc6, 0x5f, 0xfe,
    0x70, 0x7f, 0xff, 0xc3, 0xff, 0xfe, 0x1f, 0xff,
    0xf0, 0xff, 0xff, 0x87, 0xff, 0xfc, 0x3f, 0xfb,
    0x7f, 0xff, 0x51, 0xf, 0xfe, 0xea, 0xaf, 0x41,
    0xff, 0xdf, 0x7c, 0x87, 0xff, 0x7e, 0x81, 0xff,
    0xdf, 0x74, 0x3f, 0xfb, 0xf2, 0x1f, 0xfd, 0xf9,
    0xf, 0xfe, 0xfc, 0x87, 0xff, 0x7e, 0xf, 0xe5,
    0xab, 0xff, 0x82, 0xa0, 0xff, 0xe2, 0xc1, 0xf7,
    0x52, 0xff, 0xf0, 0x69, 0xe8, 0x3f, 0xf8, 0x48,
    0x7f, 0xf4, 0x1e, 0xf, 0xfe, 0xa, 0x1f, 0xfd,
    0x16, 0xf, 0xfe, 0x4, 0x1f, 0xfd, 0x26, 0xf,
    0xfe, 0xfa, 0x1f, 0xfe, 0x8, 0x3f, 0xe4, 0x3f,
    0xfa, 0x68, 0x7f, 0xff, 0xc3, 0xff, 0xfe, 0x1f,
    0xfc, 0xd4, 0x3f, 0xe4, 0x35, 0x3, 0xff, 0x9b,
    0x7, 0xff, 0x11, 0x58, 0x7f, 0xf2, 0xd0, 0xff,
    0x90, 0xd0, 0x5c, 0x1f, 0xfc, 0x98, 0x3f, 0xec,
    0x32, 0x19, 0xd0, 0xff, 0xe2, 0xb8, 0x7f, 0xf0,
    0x10, 0xa0, 0xfa, 0xe4, 0x3f, 0xf8, 0x34, 0xf,
    0xfe, 0x2, 0x19, 0xf, 0xe6, 0xe5, 0x7, 0x37,
    0x90, 0xff, 0xe0, 0xc1, 0x41, 0xff, 0xc1, 0x69,
    0xfd, 0x21, 0xff, 0xc3, 0x83, 0x21, 0xff, 0xd9,
    0x50, 0x7f, 0xf7, 0xa0, 0xed, 0xf, 0xfe, 0xb3,
    0x87, 0xd6, 0x1f, 0xfd, 0x46, 0xf, 0xf7, 0x21,
    0xff, 0xd0, 0xa0, 0x7f, 0xf0, 0x1b, 0x83, 0xff,
    0x99, 0x68, 0x7f, 0xf1, 0x1f, 0x41, 0xff, 0xc6,
    0x6d, 0xf, 0xfe, 0x4b, 0xf4, 0xa0, 0xfc, 0xde,
    0x90, 0xff, 0xe0, 0x0,

    /* U+0036 "6" */
    0xf, 0xfe, 0x3b, 0x4f, 0xfa, 0x88, 0x7f, 0xf4,
    0x1f, 0x4a, 0xf, 0x95, 0x7a, 0x43, 0xff, 0x95,
    0x70, 0x7f, 0xf1, 0x5b, 0xc8, 0x7f, 0xf1, 0x6d,
    0xf, 0xfe, 0x5d, 0xc1, 0xff, 0xc2, 0xd0, 0xff,
    0xe7, 0xb8, 0x7f, 0xce, 0x1f, 0xfd, 0x24, 0x3f,
    0xcc, 0x1f, 0xfd, 0x38, 0x3f, 0x98, 0x3f, 0xfa,
    0x68, 0x7f, 0xa0, 0xff, 0xea, 0x41, 0xfd, 0x87,
    0xff, 0x5, 0xbf, 0xf4, 0x87, 0xc8, 0x7f, 0x41,
    0xff, 0xc0, 0xb9, 0xf, 0xcd, 0xe8, 0x34, 0x1f,
    0xc8, 0x7f, 0x9d, 0xf, 0xfe, 0x1b, 0xc4, 0x1f,
    0xd0, 0x7f, 0xa8, 0x1f, 0xfc, 0x77, 0x43, 0xf9,
    0xf, 0xe9, 0xf, 0xfe, 0x9c, 0x1f, 0xe4, 0x3f,
    0xfa, 0x88, 0x7f, 0x61, 0xff, 0xd4, 0x43, 0xf9,
    0xf, 0xfe, 0xae, 0x1f, 0xd0, 0x7f, 0xf5, 0x50,
    0xff, 0xf4, 0x21, 0xf9, 0xbf, 0xea, 0x21, 0xff,
    0xc1, 0x43, 0xfb, 0xe, 0x7d, 0x21, 0xf2, 0xae,
    0xf, 0xfb, 0xf, 0xe4, 0x27, 0x83, 0xff, 0x86,
    0xf0, 0x7f, 0x21, 0xff, 0xc0, 0xa0, 0x7f, 0xf1,
    0xdd, 0xf, 0xfe, 0x3c, 0x87, 0xff, 0x2a, 0x43,
    0xff, 0x8b, 0x21, 0xff, 0xcc, 0x90, 0xff, 0xe1,
    0xa8, 0x3f, 0xf9, 0xd2, 0x1f, 0xfc, 0x28, 0x3f,
    0xfa, 0x10, 0x7f, 0xf2, 0xda, 0xe4, 0x3f, 0xf8,
    0x50, 0x10, 0xff, 0xe2, 0x3e, 0x97, 0xaf, 0x21,
    0xff, 0x21, 0xff, 0xc6, 0xa0, 0x7f, 0xd4, 0xf,
    0xf9, 0xf, 0xfe, 0x26, 0x87, 0xff, 0x5, 0x83,
    0xfd, 0x8, 0x7f, 0xf0, 0x60, 0xff, 0xe2, 0x28,
    0x3f, 0xf9, 0x8a, 0xf, 0xfe, 0x2c, 0x1f, 0xe4,
    0x3f, 0xf8, 0x30, 0x7f, 0xf1, 0xd0, 0xff, 0xef,
    0xe1, 0xfd, 0x87, 0xff, 0x1, 0xf, 0xfe, 0x42,
    0x1f, 0xf2, 0x1f, 0xff, 0xf0, 0xff, 0xe0, 0x61,
    0xff, 0xd3, 0x43, 0xfe, 0x43, 0xfc, 0x87, 0xff,
    0x55, 0xf, 0xfe, 0x96, 0x1f, 0xd8, 0x30, 0xff,
    0x21, 0xff, 0xc7, 0x43, 0xff, 0x80, 0x87, 0xfa,
    0xf, 0xfe, 0x34, 0x1f, 0xe4, 0x24, 0x3f, 0xd8,
    0x7f, 0xf1, 0x14, 0x1f, 0xfc, 0x28, 0x3f, 0xe8,
    0x3f, 0xf8, 0x4c, 0x1f, 0xe8, 0x39, 0xf, 0xf3,
    0xa1, 0xff, 0x50, 0x3f, 0xe4, 0x3a, 0xf, 0xfe,
    0x5, 0xc8, 0x73, 0x68, 0x7f, 0xc8, 0x7d, 0x87,
    0xff, 0x5, 0xbf, 0xa4, 0x3f, 0xf8, 0x30, 0x7e,
    0x83, 0xff, 0xab, 0x7, 0xf2, 0x83, 0xff, 0xa6,
    0xa0, 0xff, 0x48, 0x7f, 0xf4, 0x58, 0x3f, 0xf8,
    0x14, 0xf, 0xfe, 0x7b, 0x7, 0xff, 0x9, 0xc3,
    0xff, 0x9b, 0x40, 0xff, 0xe2, 0xf0, 0x7f, 0xf2,
    0x5d, 0xf, 0xfe, 0x3b, 0xc8, 0x7f, 0xf1, 0x2e,
    0xf, 0xfe, 0x5b, 0x72, 0x83, 0xe5, 0x5e, 0x43,
    0xfe,

    /* U+0037 "7" */
    0x7f, 0xff, 0xbe, 0x1f, 0xff, 0xf0, 0xff, 0xff,
    0x87, 0xff, 0xfc, 0x3f, 0xff, 0xe1, 0xff, 0xe7,
    0x43, 0xfc, 0xd7, 0xff, 0x21, 0xf, 0xfa, 0xf,
    0xf4, 0xbf, 0xfc, 0x80, 0xff, 0x90, 0xff, 0xea,
    0x21, 0xfe, 0x83, 0xff, 0xa7, 0x7, 0xf9, 0xf,
    0xfe, 0xa2, 0x1f, 0xe8, 0x3f, 0xfa, 0x70, 0x7f,
    0x90, 0xff, 0xea, 0x21, 0xfe, 0x83, 0xff, 0xa7,
    0x7, 0xf9, 0xc, 0xd7, 0xf0, 0x7f, 0xf1, 0x90,
    0xff, 0x41, 0xcb, 0xfc, 0x1f, 0xfc, 0x58, 0x3f,
    0xfb, 0xe8, 0x7f, 0xa0, 0xff, 0xe9, 0xa1, 0xff,
    0x21, 0xff, 0xd3, 0x83, 0xfd, 0x7, 0xff, 0x4d,
    0xf, 0xf9, 0xf, 0xfe, 0x9c, 0x1f, 0xe8, 0x3f,
    0xfa, 0x68, 0x7f, 0xc8, 0x7f, 0xf4, 0xe0, 0xff,
    0x41, 0xff, 0xd3, 0x43, 0xfe, 0x43, 0xff, 0xa7,
    0x7, 0xfa, 0xf, 0xfe, 0x9a, 0x1f, 0xf2, 0x1f,
    0xfd, 0x38, 0x3f, 0xc8, 0x7f, 0xf4, 0xd0, 0xff,
    0xa0, 0xff, 0xe9, 0xc1, 0xfe, 0x43, 0xff, 0xa6,
    0x87, 0xfd, 0x7, 0xff, 0x4f, 0xf, 0xf2, 0x1f,
    0xfd, 0x44, 0x3f, 0xd0, 0x7f, 0xf4, 0xe0, 0xff,
    0x21, 0xff, 0xd4, 0x43, 0xfd, 0x7, 0xff, 0x4e,
    0xf, 0xf2, 0x1f, 0xfd, 0x44, 0x3f, 0xd0, 0x7f,
    0xf4, 0xe0, 0xff, 0x21, 0xff, 0xd4, 0x43, 0xfd,
    0x87, 0xff, 0x4e, 0xf, 0xf9, 0xf, 0xfe, 0x9a,
    0x1f, 0xe8, 0x3f, 0xfa, 0x70, 0x7f, 0xc8, 0x7f,
    0xf4, 0xd0, 0xff, 0x41, 0xff, 0xd3, 0x83, 0xfe,
    0x43, 0xff, 0xa6, 0x87, 0xfa, 0xf, 0xfe, 0x9a,
    0x1f, 0xf2, 0x1f, 0xfd, 0x38, 0x3f, 0xd0, 0x7f,
    0xf4, 0xd0, 0xff, 0x90, 0xff, 0xe9, 0xc1, 0xfe,
    0x83, 0xff, 0xa6, 0x87, 0xfc, 0x87, 0xff, 0x4e,
    0xf, 0xf2, 0x1f, 0xfd, 0x34, 0x3f, 0xe8, 0x3f,
    0xfa, 0x70, 0x7f, 0x90, 0xff, 0xe9, 0xa1, 0xff,
    0x41, 0xff, 0xca,

    /* U+0038 "8" */
    0xf, 0xfe, 0x1b, 0x4f, 0xfd, 0x21, 0xff, 0xd0,
    0xbd, 0x28, 0x3f, 0x37, 0xa4, 0x3f, 0xf9, 0x5e,
    0x43, 0xff, 0x8a, 0xda, 0x1f, 0xfc, 0x6b, 0xf,
    0xfe, 0x5d, 0x87, 0xff, 0x13, 0x43, 0xff, 0x9d,
    0xa1, 0xff, 0xc1, 0xc3, 0xff, 0xa3, 0x21, 0xff,
    0x61, 0xff, 0xd3, 0x83, 0xfd, 0x7, 0xff, 0xd,
    0x60, 0xff, 0xe1, 0xe1, 0xfc, 0x87, 0xfc, 0xfd,
    0x57, 0xd2, 0x1f, 0xf2, 0x1f, 0x21, 0xfe, 0x78,
    0x3f, 0x9a, 0x7, 0xfb, 0xf, 0xb0, 0xfe, 0xa0,
    0x7f, 0xf0, 0x5c, 0x3f, 0x90, 0xf9, 0xf, 0xca,
    0xf, 0xfe, 0x24, 0x1f, 0xc8, 0x7f, 0xf0, 0xf0,
    0xff, 0xe2, 0xa1, 0xff, 0xcd, 0x43, 0xff, 0x8c,
    0x87, 0xff, 0xfc, 0x3f, 0xff, 0x88, 0x7e, 0x43,
    0xff, 0x8c, 0x87, 0xe4, 0x3d, 0x7, 0xe8, 0x3f,
    0xf8, 0xb0, 0x7e, 0x43, 0xf2, 0x1f, 0xa0, 0xff,
    0xe1, 0xa8, 0x3f, 0x61, 0xfa, 0xf, 0xce, 0x87,
    0xff, 0x2, 0x81, 0xf9, 0x41, 0xfd, 0x7, 0xf5,
    0xc8, 0x79, 0xb4, 0x3f, 0xa0, 0xff, 0x30, 0x7f,
    0x9b, 0xfd, 0x21, 0xfe, 0xc3, 0xff, 0x80, 0xc1,
    0xff, 0xd0, 0xc3, 0xff, 0x84, 0xe1, 0xff, 0xcd,
    0x70, 0xff, 0xe2, 0xf0, 0x7f, 0xf2, 0xa8, 0x1f,
    0xfc, 0x6a, 0x7, 0xff, 0x2a, 0x81, 0xff, 0xc4,
    0xb4, 0x3f, 0xf9, 0x8e, 0x87, 0xff, 0x7, 0x43,
    0xff, 0xa1, 0x40, 0xff, 0x38, 0x7f, 0xf4, 0xdc,
    0x3f, 0x30, 0x7f, 0xf0, 0x15, 0x5e, 0x43, 0xff,
    0x83, 0x87, 0xd0, 0x7f, 0x9b, 0xa2, 0xfa, 0xf2,
    0x1f, 0xf4, 0x1d, 0x87, 0xfa, 0x88, 0x7f, 0xf0,
    0x2c, 0x3f, 0xca, 0x9, 0xf, 0xf6, 0x87, 0xff,
    0x13, 0x43, 0xfa, 0xa, 0xf, 0xe8, 0x3f, 0xf8,
    0xf0, 0x7f, 0x90, 0xff, 0xe0, 0x21, 0xff, 0xc8,
    0x83, 0xfb, 0x20, 0xfe, 0x83, 0xff, 0x92, 0x87,
    0xf2, 0x1f, 0xfe, 0x14, 0x3f, 0x90, 0xff, 0xe5,
    0x21, 0xfc, 0x87, 0xff, 0x55, 0xf, 0xfe, 0x42,
    0x1f, 0xfd, 0xfc, 0x3f, 0xfb, 0xe8, 0x7f, 0xf2,
    0x50, 0xff, 0x28, 0x3f, 0xc8, 0x7f, 0xf2, 0x20,
    0xff, 0xb0, 0xff, 0x48, 0x7f, 0xf1, 0xb0, 0xff,
    0x22, 0x1f, 0xf4, 0x87, 0xff, 0x13, 0xf, 0xfb,
    0x2, 0x1f, 0xf5, 0xa1, 0xff, 0x36, 0x1f, 0xfc,
    0x4, 0x10, 0x7f, 0xf0, 0x6f, 0x4b, 0xd4, 0xe4,
    0x3f, 0xf8, 0x10, 0x68, 0x3f, 0xf8, 0x6d, 0x72,
    0x83, 0xff, 0x84, 0xa0, 0xca, 0xf, 0xfe, 0xc4,
    0x1e, 0x90, 0xff, 0xeb, 0x61, 0xfa, 0x81, 0xff,
    0xd3, 0x70, 0xff, 0x38, 0x7f, 0xf4, 0x68, 0x1f,
    0xfc, 0x1e, 0xf, 0xfe, 0x6d, 0xa1, 0xff, 0xc3,
    0x7c, 0x87, 0xff, 0x1d, 0xb4, 0x3f, 0xf9, 0x17,
    0xa5, 0x7, 0xf2, 0xaf, 0x48, 0x7f, 0xc0,

    /* U+0039 "9" */
    0xf, 0xfe, 0x12, 0xaf, 0xfa, 0x88, 0x7f, 0xf4,
    0x1b, 0xa2, 0x1f, 0x2a, 0xf4, 0x1f, 0xfc, 0xb7,
    0x90, 0xff, 0xe2, 0x3c, 0x1f, 0xfc, 0x8a, 0x7,
    0xff, 0x25, 0xd0, 0xff, 0xe2, 0xe8, 0x7f, 0xf3,
    0x2c, 0x3f, 0xf8, 0x78, 0x7f, 0xf4, 0x30, 0xff,
    0xe0, 0xe1, 0xff, 0xd2, 0xc3, 0xfe, 0xc3, 0xff,
    0xa9, 0x87, 0xf2, 0x1f, 0xfd, 0x68, 0x3f, 0x41,
    0xff, 0xc1, 0x6f, 0xe9, 0xf, 0xfe, 0x2, 0x83,
    0xd0, 0x7f, 0xf0, 0x2e, 0x43, 0x9b, 0x83, 0xfe,
    0x83, 0xc8, 0x7f, 0x9d, 0xf, 0xf9, 0xc3, 0xfe,
    0x83, 0xff, 0x89, 0x7, 0xff, 0xf, 0xf, 0xf2,
    0x19, 0xf, 0xf6, 0x1f, 0xfc, 0x58, 0x3f, 0xd0,
    0x58, 0x7f, 0x21, 0xff, 0xc6, 0x43, 0xfc, 0x84,
    0x87, 0xf6, 0x1f, 0xfc, 0x78, 0x3f, 0xf9, 0x68,
    0x7f, 0xf1, 0xd0, 0xff, 0x41, 0xff, 0xdf, 0x43,
    0xff, 0xfe, 0x1f, 0xfe, 0x14, 0x3f, 0xe4, 0x3f,
    0xe4, 0x3f, 0xf8, 0xf8, 0x7f, 0xd8, 0x87, 0xf6,
    0x1f, 0xfc, 0x74, 0x3f, 0xf8, 0x38, 0x7f, 0x21,
    0xff, 0xc6, 0x83, 0xff, 0x84, 0x87, 0xfb, 0xf,
    0xfe, 0x22, 0x83, 0xff, 0x80, 0x87, 0xff, 0x7,
    0xf, 0xfe, 0x15, 0x3, 0xff, 0x89, 0x7, 0xfd,
    0xa1, 0xfe, 0x74, 0x3f, 0xf8, 0xa8, 0x7f, 0xf0,
    0x2e, 0x8b, 0xa9, 0xc1, 0xff, 0xc8, 0x83, 0xff,
    0x82, 0xaa, 0xca, 0xf, 0xfe, 0x52, 0x83, 0xff,
    0xa0, 0x87, 0xf2, 0x1a, 0xf, 0xfe, 0x7e, 0x1f,
    0xfc, 0x4c, 0x3f, 0xf9, 0xb0, 0x7f, 0xf1, 0xb4,
    0x3f, 0xf9, 0x5a, 0x1f, 0xf6, 0x1f, 0x50, 0x3f,
    0xf8, 0xee, 0x12, 0x1f, 0xfc, 0x67, 0x83, 0xff,
    0x86, 0xf0, 0x7f, 0xf0, 0x90, 0xff, 0x3e, 0x90,
    0xf9, 0x57, 0x7, 0xff, 0x49, 0xbf, 0xea, 0x21,
    0xf2, 0x1f, 0xc8, 0x7f, 0xf5, 0x70, 0xfe, 0xc3,
    0xff, 0xaa, 0x87, 0xf2, 0x1f, 0xfd, 0x44, 0x3f,
    0xfb, 0xf0, 0x7f, 0x21, 0xff, 0xd4, 0x83, 0xfd,
    0x7, 0xff, 0x4d, 0x41, 0xfc, 0x87, 0xff, 0x52,
    0xf, 0xf4, 0x1f, 0xde, 0x43, 0xff, 0x8c, 0xe1,
    0xfe, 0x43, 0xf9, 0x5, 0xa1, 0xff, 0xc3, 0xa0,
    0x7f, 0xd0, 0x7f, 0x41, 0xae, 0x43, 0xf9, 0xf2,
    0x1f, 0xf4, 0x1f, 0xc8, 0x7c, 0xdf, 0xfd, 0x7,
    0xff, 0x5, 0x41, 0xfd, 0x7, 0xff, 0x52, 0xf,
    0xe4, 0x3f, 0xfa, 0x98, 0x7f, 0xa0, 0xff, 0xe9,
    0x38, 0x7f, 0x90, 0xff, 0xe9, 0x30, 0x7f, 0xce,
    0x87, 0xff, 0x3e, 0x81, 0xff, 0xc2, 0xb4, 0x3f,
    0xf9, 0x76, 0x87, 0xff, 0x16, 0xf2, 0x1f, 0xfc,
    0x56, 0xd0, 0xff, 0xe5, 0x5e, 0xa2, 0x83, 0xe6,
    0x9c, 0x87, 0xff, 0xc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 790, .box_w = 43, .box_h = 56, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 790, .box_w = 23, .box_h = 56, .ofs_x = 8, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 923, .adv_w = 790, .box_w = 46, .box_h = 56, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1143, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1371, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1732, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1983, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2350, .adv_w = 790, .box_w = 44, .box_h = 56, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
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
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
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
const lv_font_t lv_font_montserratMedium_80 = {
#else
lv_font_t lv_font_montserratMedium_80 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 56,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -6,
    .underline_thickness = 4,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if LV_FONT_MONTSERRATMEDIUM_80*/

