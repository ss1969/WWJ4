/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct {
    lv_obj_t *screen_watting;
    bool      screen_watting_del;
    lv_obj_t *screen_watting_lb_coin;
    lv_obj_t *screen_watting_label_3;
    lv_obj_t *screen_watting_cont_1;
    lv_obj_t *screen_watting_qrcode;
    lv_obj_t *screen_watting_lb_time;
    lv_obj_t *screen_watting_label_4;
    lv_obj_t *screen_watting_label_5;
    lv_obj_t *screen_tickets;
    bool      screen_tickets_del;
    lv_obj_t *screen_tickets_cont_1;
    lv_obj_t *screen_tickets_img_user;
    lv_obj_t *screen_tickets_lb_user_id;
    lv_obj_t *screen_tickets_lb_got_ticket;
    lv_obj_t *screen_tickets_lb_save_ticket;
    lv_obj_t *screen_tickets_lb_not_save;
    lv_obj_t *screen_tickets_qrcode;
    lv_obj_t *screen_tickets_btn_save_exit;
    lv_obj_t *screen_tickets_btn_save_exit_label;
    lv_obj_t *screen_tickets_progress_bar;
    lv_obj_t *screen_tickets_label_6;
    lv_obj_t *screen_tickets_label_1;
    lv_obj_t *screen_tickets_label_2;
    lv_obj_t *screen_tickets_label_3;
    lv_obj_t *screen_tickets_saving;
    lv_obj_t *screen_tickets_label_4;
    lv_obj_t *screen_tickets_label_5;
    lv_obj_t *screen_unbind;
    bool      screen_unbind_del;
    lv_obj_t *screen_unbind_cont_1;
    lv_obj_t *screen_unbind_lb_device_id;
    lv_obj_t *screen_unbind_qrcode;
    lv_obj_t *screen_unbind_btn_1;
    lv_obj_t *screen_unbind_btn_1_label;
    lv_obj_t *screen_unbind_btn_2;
    lv_obj_t *screen_unbind_btn_2_label;
    lv_obj_t *screen_unbind_btn_3;
    lv_obj_t *screen_unbind_btn_3_label;
    lv_obj_t *screen_unbind_btn_4;
    lv_obj_t *screen_unbind_btn_4_label;
    lv_obj_t *screen_unbind_lbSignal;
    lv_obj_t *screen_unbind_label_1;
} lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui *ui);

void ui_init_style(lv_style_t *style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t **new_scr, bool new_scr_del, bool *old_scr_del, ui_setup_scr_t setup_scr, lv_screen_load_anim_t anim_type,
                           uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void *var, uint32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb, uint32_t repeat_cnt,
                  uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay, lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb,
                  lv_anim_completed_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_bottom_layer(void);

void setup_ui(lv_ui *ui);

void video_play(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;

void setup_scr_screen_watting(lv_ui *ui);
void setup_scr_screen_tickets(lv_ui *ui);
void setup_scr_screen_unbind(lv_ui *ui);

LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_22)
LV_FONT_DECLARE(lv_font_montserratMedium_80)
LV_FONT_DECLARE(lv_font_NotoSansCJKscMedium_18)
LV_FONT_DECLARE(lv_font_NotoSansCJKscMedium_22)
LV_FONT_DECLARE(lv_font_NotoSansCJKscMedium_26)
LV_FONT_DECLARE(lv_font_NotoSansCJKscMedium_36)

#ifdef __cplusplus
}
#endif
#endif
