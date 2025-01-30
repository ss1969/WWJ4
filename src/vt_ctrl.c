/*------------------------------------------------------------------------
 * Reference : http://www.termsys.demon.co.uk/vtansi.htm
 *------------------------------------------------------------------------
 */

#include <string.h>
#include <stdio.h>

#include "wrapper.h"
#include "vt_ctrl.h"

extern int uart_print(const char *format, ...);

/*------------------------------------------------------------------------
 * Function:   CON_VT_Set_Cursor_to_XY()
 * Purpose:    Moves the cursor to the specified position. If you do
 *             not specify a position, the cursor moves to the home
 *             position-the upper-left corner of the screen ( line 0,
 *             column 0 ).
 *
 * Parameters:
 *    Input:   ioctl_T *icb
 *             column = X.
 *             line =   Y.
 *    Output:  None.
 * Returns : None.
 * Remark : <ESC>[{ROW};{COLUMN}H
 *------------------------------------------------------------------------
 */
void CON_VT_Set_Cursor_to_XY(uint16_t row, uint16_t column) {
    char          escape_str[12], *temp_ptr;
    char          str[8];
    unsigned char i;

    /* Reserve 12 bytes space for Escape sequence */
    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '[';

    // num2str((UI32_T)row, str);
    sprintf(str, "%d", row);
    for (i = 0; str[i] != VT_NULL; i++)
        *temp_ptr++ = str[i];

    *temp_ptr++ = ';';

    sprintf(str, "%d", column);
    for (i = 0; str[i] != VT_NULL; i++)
        *temp_ptr++ = str[i];

    *temp_ptr++ = 'H';
    *temp_ptr   = VT_NULL;

    uart_print("%s", escape_str);
}

/*------------------------------------------------------------------------
 * Function:   CON_VT_Set_Text_Attributes
 *
 * Purpose:    Set Text attributes
 * Parameters:
 *    Input:   ioctl_T *icb
 *             attribute =  0	Reset all attributes
 *                          1	Bright
 *                          2	Dim
 *                          4	Underscore
 *                          5	Blink
 *                          7	Reverse
 *                          8	Hidden
 *
 *                          	Foreground Colours
 *                          30	Black
 *                          31	Red
 *                          32	Green
 *                          33	Yellow
 *                          34	Blue
 *                          35	Magenta
 *                          36	Cyan
 *                          37	White
 *
 *                          	Background Colours
 *                          40	Black
 *                          41	Red
 *                          42	Green
 *                          43	Yellow
 *                          44	Blue
 *                          45	Magenta
 *                          46	Cyan
 *                          47	White
 *    Output:  None.
 * Returns : None.
 * Remark : <ESC>[{attr1};...;{attrn}m
 *------------------------------------------------------------------------
 */
void CON_VT_Set_Text_Attributes(uint16_t attribute) {
    char          escape_str[20], *temp_ptr;
    char          str[8];
    unsigned char i;

    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '[';

    sprintf(str, "%d", attribute);
    for (i = 0; str[i] != VT_NULL; i++)
        *temp_ptr++ = str[i];

    *temp_ptr++ = 'm';
    *temp_ptr   = VT_NULL;

    uart_print("%s", escape_str);
}

/*------------------------------------------------------------------------
 * Function:   CON_VT_Save_Cursor_Position
 * Purpose:    Save Cursor Position
 * Parameters:
 *    Input:  ioctl_T *icb
 *    Output: None.
 * Returns : None.
 * Remark : <ESC>7
 *------------------------------------------------------------------------
 */
void CON_VT_Save_Cursor_Position(void) {
    char escape_str[8], *temp_ptr;

    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '7';

    *temp_ptr = VT_NULL;
    uart_print("%s", escape_str);
}

/*------------------------------------------------------------------------
 * Function:   CON_VT_Restore_Cursor_Position
 * Purpose:    Restore Cursor Position
 *
 * Parameters:
 *    Input:   ioctl_T *icb
 *    Output:  None.
 * Returns : None
 * Remark : <ESC>8
 *------------------------------------------------------------------------
 */
void CON_VT_Restore_Cursor_Position(void) {
    char escape_str[8], *temp_ptr;

    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '8';

    *temp_ptr = VT_NULL;
    uart_print("%s", escape_str);
}

/*------------------------------------------------------------------------
 * Function:   CON_VT_Scroll_Screen
 * Purpose:    Scroll the entire screen
 *
 * Parameters:
 *    Input:   ioctl_T *icb
 *    Output:  None.
 * Returns : None
 * Remark : <ESC>[r
 *------------------------------------------------------------------------
 */
void CON_VT_Scroll_Screen(void) {
    char escape_str[8], *temp_ptr;

    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '[';
    *temp_ptr++ = 'r';

    *temp_ptr = VT_NULL;
    uart_print("%s", escape_str);
}

/*------------------------------------------------------------------------
 * Function:   CON_VT_Erase_Screen
 * Purpose:    Erase Text on the VT100 Screen.
 * Parameters:
 *    Input:   erase_mode =  0 : Erase from the cursor to the end of
 *                               the screen.
 *                           1 : Erase from the beginning of the screen to
 *                               the cursor.
 *                           2 : Clears the screen but do not moves the
 *                               cursor position.
 *             ioctl_T *icb
 *    Output:  None.
 * Returns : <ESC>[{erase_mode}J
 *------------------------------------------------------------------------
 */
void CON_VT_Erase_Screen(uint16_t erase_mode) {
    char escape_str[8], *temp_ptr;

    temp_ptr    = escape_str;
    *temp_ptr++ = CON_VT_ESC;
    *temp_ptr++ = '[';

    if (erase_mode == 0)
        *temp_ptr++ = '0';
    else if (erase_mode == 1)
        *temp_ptr++ = '1';
    else if (erase_mode == 2)
        *temp_ptr++ = '2';

    *temp_ptr++ = 'J';
    *temp_ptr   = VT_NULL;

    uart_print("%s", escape_str);
}
