#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "lcd.h"

#include "gui.h"

void gui_update_customer(WCustomer *info) {
    LUAT_DEBUG_PRINT("userportrait: %s", info->userPortrait);
    LUAT_DEBUG_PRINT("nickname: %s", info->nickName);
    LUAT_DEBUG_PRINT("user ID: %d", info->userID);
}

void gui_update_ticket_save(int countdown) {
    LUAT_DEBUG_PRINT("ticktesave countdown: %s", countdown);
}