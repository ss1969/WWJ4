#ifndef  __VT_CTRL_
#define  __VT_CTRL_

#include <stdint.h>

typedef const char **ARGV_T;

#define VT_Erase_Down	0
#define VT_Erase_Up		1
#define VT_Erase_Screen	2

/*
 * VT100 Character Set
 */
#define  CON_VT_ASCII_CHAR_SET 'B'
#define  CON_VT_DEC_GRAPHIC    '0'

/*
 * VT100 DEC Special Graphic : box line ASCII code
 */
#define  CON_VT_BOX_LEFTUP     0x6c  /* ?*/
#define  CON_VT_BOX_RIGHTUP    0x6b  /* ?*/
#define  CON_VT_BOX_LEFTDOWN   0x6d  /* ?*/
#define  CON_VT_BOX_RIGHTDOWN  0x6a  /* ?*/
#define  CON_VT_BOX_LEFT       0x78  /* ?*/
#define  CON_VT_BOX_RIGHT      0x78  /* ?*/
#define  CON_VT_BOX_UP         0x71  /* ?*/
#define  CON_VT_BOX_DOWN       0x71  /* ?*/
#define  CON_VT_BOX_CROSS      0x6e  /* ?*/
#define  CON_VT_BOX_LEFT_T     0x74  /* ?*/
#define  CON_VT_BOX_RIGHT_T    0x75  /* ?*/

/*
 * VT100 Erase Screen mode
 */
#define  CON_VT_SCREEN_FROM_CURSOR2END_ERASE     '0'
#define  CON_VT_SCREEN_FROM_BEGIN2CURSOR_ERASE   '1'
#define  CON_VT_SCREEN_COMPLETE_ERASE            '2'


/*
 * VT100 Text Attributes
 */
#define  CON_VT_TEXT_NORMAL          0
#define  CON_VT_TEXT_HIGH_INTENSITY  1
#define  CON_VT_TEXT_BLINK           5
#define  CON_VT_TEXT_INVERSE         7
#define  CON_VT_TEXT_CONCEALED       8
#define  CON_VT_TEXT_ASCII           10
#define  CON_VT_TEXT_GRAPHICS        12

/*
 * ASCII code : keystroke
 */
#define  CON_VT_CTRL_C	    0x03
#define  CON_VT_CTRL_D	    0x04
#define  CON_VT_ESC         0x1b
#define  CON_VT_BACKSPACE   0x08  // '\b'
#define  CON_VT_CR          0x0d  // '\r'
#define  CON_VT_LF          0x0a  // '\n'
#define  CON_VT_BACK_TAB    0x08
#define  CON_VT_TAB         0x09
#define  CON_VT_SPACE       0x20
#define  CON_VT_DEL         0x7f
#define  CON_VT_BRACKET     0x5b
#define  VT_NULL            0

/*
 * The definition of Serial port transmit data type
 */
#define  CON_VT_STRING_MODE      -1

void CON_VT_Set_Cursor_to_XY(uint16_t row, uint16_t column);
void CON_VT_Set_Text_Attributes(uint16_t attribute);
void CON_VT_Save_Cursor_Position(void);
void CON_VT_Restore_Cursor_Position(void);
void CON_VT_Scroll_Screen(void);
void CON_VT_Erase_Screen(uint16_t erase_mode);

#endif   /* end of ifndef CON_VT */
