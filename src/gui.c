#include "common_api.h"
#include "luat_rtos.h"
#include "luat_debug.h"
#include "luat_timer.h"

#include "lcd.h"
#include "lvgl.h"
#include "gui.h"
#include "sysvars.h"

lv_ui                    ui;
static luat_rtos_timer_t timer0                       = NULL;
static int               ticket_save_countdown        = 0;
static int               ticket_save_countdown_backup = 0;

/* init */
void gui_init(void) {
    lv_theme_apply(lv_layer_bottom());
    ui.screen_watting_del = true;
    ui.screen_tickets_del = true;
    ui.screen_unbind_del  = true;
    setup_scr_screen_tickets(&ui);
    setup_scr_screen_unbind(&ui);
    setup_scr_screen_watting(&ui);

    lv_obj_set_scroll_dir(ui.screen_tickets, LV_DIR_NONE);
    lv_obj_set_scroll_dir(ui.screen_unbind, LV_DIR_NONE);
    lv_obj_set_scroll_dir(ui.screen_watting, LV_DIR_NONE);

    gui_unbind_set_sn(svSystemID);
    gui_waiting_set_coin(svCoinPerPlay);
    gui_waiting_set_machine(svMachineName);
    gui_waiting_set_qrcode(svPayUrl);

    lv_screen_load(ui.screen_unbind);
}

void gui_all_set_signal(bool ready, char *card, int signal) {
    lv_obj_t *s = lv_screen_active();
    if (s == ui.screen_unbind) {
        char str[48] = {0};
        sprintf(str, "%s | 信号 %d | %s", card, signal, ready ? "R" : "NR");
        lv_label_set_text(ui.screen_unbind_lbSignal, str);
    }
    else if (s == ui.screen_tickets) {
    }
    else if (s == ui.screen_watting) {
    }
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

/********************* WAIT *********************/
void gui_waiting_switch(void) {
    lv_screen_load(ui.screen_watting);
}

void gui_waiting_set_machine(char *name) {
    lv_label_set_text(ui.screen_watting_lb_machine, name);
}

void gui_waiting_set_comm_time(int second) {
    char str[8] = {0};
    sprintf(str, "%ds", second);
    lv_label_set_text(ui.screen_watting_lb_time, str);
}

void gui_waiting_set_qrcode(wchar_t *sn) {
    char str[48] = {0};
    sprintf(str, "{\"sn\":\"%s\"}", sn);
    lv_qrcode_update(ui.screen_watting_qrcode, str, strlen(str));
}

void gui_waiting_set_coin(char coin) {
    char str[8] = {0};
    sprintf(str, "%d", coin);
    lv_label_set_text(ui.screen_watting_lb_coin, str);
}

/********************* TICKET *********************/

void gui_ticket_switch(void) {
    lv_screen_load(ui.screen_tickets);
}

void gui_ticket_set_customer_info(WCustomer *info) {
    LUAT_DEBUG_PRINT("userportrait: %s", info->userPortrait);
    LUAT_DEBUG_PRINT("nickname: %s", info->nickName);
    LUAT_DEBUG_PRINT("user ID: %d", info->userID);

    char str[32];
    snprintf(str, 15, "%s", info->nickName);
    lv_label_set_text(ui.screen_tickets_lb_nickname, str);

    snprintf(str, 8, "%d", info->userID);
    lv_label_set_text(ui.screen_tickets_lb_user_id, str);

    lv_image_set_src(ui.screen_tickets_img_user, LV_SYMBOL_OK); // k 以后处理
}

void gui_ticket_set_numbers(int got, int saved, int not_save) {
    char str[8];
    snprintf(str, 6, "%d", got);
    lv_label_set_text(ui.screen_tickets_lb_got_ticket, str);
    snprintf(str, 6, "%d", saved);
    lv_label_set_text(ui.screen_tickets_lb_save_ticket, str);
    snprintf(str, 6, "%d", not_save);
    lv_label_set_text(ui.screen_tickets_lb_not_save, str);
}

void gui_ticket_end_timer(void) {
    if (timer0 != NULL) {
        luat_rtos_timer_stop(timer0);
        luat_rtos_timer_delete(timer0);
        timer0 = NULL;
    }
}

static void timer0_callback_gui_ticket(void *param) {
    ticket_save_countdown--;
    lv_bar_set_value(ui.screen_tickets_progress_bar, ticket_save_countdown, LV_ANIM_ON);

    if (ticket_save_countdown == 0) {
        gui_ticket_end_timer();
        gui_waiting_switch();
    }
}

void gui_ticket_update_save_timer(int countdown) {
    LUAT_DEBUG_PRINT("ticktesave countdown: %s", countdown);
    if (timer0 != NULL) {
        luat_rtos_timer_stop(timer0);
        luat_rtos_timer_delete(timer0);
        timer0 = NULL;
    }
    ticket_save_countdown        = countdown;
    ticket_save_countdown_backup = countdown;
    lv_bar_set_range(ui.screen_tickets_progress_bar, 0, countdown);
    lv_bar_set_value(ui.screen_tickets_progress_bar, countdown, LV_ANIM_ON);

    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, 1000, 1, timer0_callback_gui_ticket, NULL);
}

void gui_ticket_refresh_timer(void) {
    if (timer0 == NULL)
        return;

    ticket_save_countdown = ticket_save_countdown_backup;
}
