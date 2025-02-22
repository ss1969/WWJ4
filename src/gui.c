#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"

#include "lcd.h"
#include "lvgl.h"
#include "gui.h"
#include "sysvars.h"

lv_ui ui;

/* init */
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
    gui_unbind_set_sn(svSystemID);
}

/********************* UNBIND *********************/
void gui_unbind_switch(void) {
    lv_screen_load(ui.screen_unbind);
}

void gui_unbind_set_sn(char *sn) {
    char str[48] = {0};
    sprintf(str, "{\"sn\":\"%s\"}", sn);
    lv_qrcode_update(ui.screen_unbind_qrcode, str, strlen(str));

    sprintf(str, "SN: %s", sn);
    lv_label_set_text(ui.screen_unbind_lb_device_id, str);
}

void gui_unbind_set_signal(char *card, int signal) {
    char str[48] = {0};
    sprintf(str, "%s | 信号强度 %d", card, signal);
    lv_label_set_text(ui.screen_unbind_lbSignal, str);
}

/********************* WAIT *********************/
void gui_waiting_switch(void) {
    lv_screen_load(ui.screen_watting);
}

/********************* TICKET *********************/

void gui_ticket_switch(void) {
    lv_screen_load(ui.screen_tickets);
}

void gui_update_customer(WCustomer *info) {
    LUAT_DEBUG_PRINT("userportrait: %s", info->userPortrait);
    LUAT_DEBUG_PRINT("nickname: %s", info->nickName);
    LUAT_DEBUG_PRINT("user ID: %d", info->userID);
}

void gui_update_ticket_save(int countdown) {
    LUAT_DEBUG_PRINT("ticktesave countdown: %s", countdown);
}
