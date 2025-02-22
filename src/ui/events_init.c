/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "gui.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void screen_tickets_btn_save_exit_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
        case LV_EVENT_CLICKED: {

            break;
        }
        default:
            break;
    }
}

void events_init_screen_tickets(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_tickets_btn_save_exit, screen_tickets_btn_save_exit_event_handler, LV_EVENT_ALL, ui);
}

static void screen_unbind_btn_1234_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t       *btn  = lv_event_get_target(e); // 获取事件源对象（按钮）

    switch (code) {
        case LV_EVENT_PRESSED:
            lv_obj_set_style_bg_color(ui.screen_unbind_cont_1, lv_color_hex(0x45cb6a), 0); //
            break;
        case LV_EVENT_RELEASED:
            lv_obj_set_style_bg_color(ui.screen_unbind_cont_1, lv_color_hex(0xc5f0f5), LV_PART_MAIN | LV_STATE_DEFAULT); // 0x2195f6
            break;
        default:
            break;
    }
}

void events_init_screen_unbind(lv_ui *ui) {
    lv_obj_add_event_cb(ui->screen_unbind_btn_1, screen_unbind_btn_1234_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_unbind_btn_2, screen_unbind_btn_1234_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_unbind_btn_3, screen_unbind_btn_1234_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_unbind_btn_4, screen_unbind_btn_1234_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui) {
}
