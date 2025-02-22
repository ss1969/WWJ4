#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "lcd.h"
#include "lvgl.h"
#include "gui.h"

lv_ui ui;

void gui_update_customer(WCustomer *info) {
    LUAT_DEBUG_PRINT("userportrait: %s", info->userPortrait);
    LUAT_DEBUG_PRINT("nickname: %s", info->nickName);
    LUAT_DEBUG_PRINT("user ID: %d", info->userID);
}

void gui_update_ticket_save(int countdown) {
    LUAT_DEBUG_PRINT("ticktesave countdown: %s", countdown);
}

void gui_init(void) {
    lv_theme_apply(lv_layer_bottom());
    ui.screen_watting_del = true;
    ui.screen_tickets_del = true;
    ui.screen_unbind_del  = true;
    setup_scr_screen_tickets(&ui);
    setup_scr_screen_unbind(&ui);
    setup_scr_screen_watting(&ui);
    // lv_screen_load(ui.screen_tickets);

    lv_obj_set_scroll_dir(ui.screen_tickets, LV_DIR_NONE);
    lv_obj_set_scroll_dir(ui.screen_unbind, LV_DIR_NONE);
    lv_obj_set_scroll_dir(ui.screen_watting, LV_DIR_NONE);

    lv_screen_load(ui.screen_unbind);
}
