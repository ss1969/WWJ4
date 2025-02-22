/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_tickets(lv_ui *ui)
{
    //Write codes screen_tickets
    ui->screen_tickets = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_tickets, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_tickets, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_tickets, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_tickets, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets, lv_color_hex(0xf1fcfd), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_cont_1
    ui->screen_tickets_cont_1 = lv_obj_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_tickets_cont_1, 320, 36);
    lv_obj_set_scrollbar_mode(ui->screen_tickets_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_tickets_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets_cont_1, lv_color_hex(0xc5f0f5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_img_user
    ui->screen_tickets_img_user = lv_image_create(ui->screen_tickets_cont_1);
    lv_obj_set_pos(ui->screen_tickets_img_user, 9, 5);
    lv_obj_set_size(ui->screen_tickets_img_user, 26, 28);
    lv_obj_add_flag(ui->screen_tickets_img_user, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_pivot(ui->screen_tickets_img_user, 50,50);
    lv_image_set_rotation(ui->screen_tickets_img_user, 0);

    //Write style for screen_tickets_img_user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_tickets_img_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_tickets_img_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_lb_user_id
    ui->screen_tickets_lb_user_id = lv_label_create(ui->screen_tickets_cont_1);
    lv_obj_set_pos(ui->screen_tickets_lb_user_id, 224, 8);
    lv_obj_set_size(ui->screen_tickets_lb_user_id, 86, 20);
    lv_label_set_text(ui->screen_tickets_lb_user_id, "22239494");
    lv_label_set_long_mode(ui->screen_tickets_lb_user_id, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_lb_user_id, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_lb_user_id, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_lb_user_id, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_lb_user_id, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_lb_user_id, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_lb_user_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_lb_got_ticket
    ui->screen_tickets_lb_got_ticket = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_lb_got_ticket, 106, 58);
    lv_obj_set_size(ui->screen_tickets_lb_got_ticket, 90, 25);
    lv_label_set_text(ui->screen_tickets_lb_got_ticket, "112920");
    lv_label_set_long_mode(ui->screen_tickets_lb_got_ticket, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_lb_got_ticket, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_lb_got_ticket, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_lb_got_ticket, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_lb_got_ticket, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_lb_got_ticket, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_lb_got_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_lb_save_ticket
    ui->screen_tickets_lb_save_ticket = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_lb_save_ticket, 106, 98);
    lv_obj_set_size(ui->screen_tickets_lb_save_ticket, 90, 25);
    lv_label_set_text(ui->screen_tickets_lb_save_ticket, "112000");
    lv_label_set_long_mode(ui->screen_tickets_lb_save_ticket, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_lb_save_ticket, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_lb_save_ticket, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_lb_save_ticket, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_lb_save_ticket, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_lb_save_ticket, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_lb_save_ticket, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_lb_not_save
    ui->screen_tickets_lb_not_save = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_lb_not_save, 106, 136);
    lv_obj_set_size(ui->screen_tickets_lb_not_save, 90, 25);
    lv_label_set_text(ui->screen_tickets_lb_not_save, "920");
    lv_label_set_long_mode(ui->screen_tickets_lb_not_save, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_lb_not_save, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_lb_not_save, lv_color_hex(0xff0027), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_lb_not_save, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_lb_not_save, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_lb_not_save, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_lb_not_save, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_qrcode
    ui->screen_tickets_qrcode = lv_qrcode_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_qrcode, 193, 54);
    lv_obj_set_size(ui->screen_tickets_qrcode, 110, 110);
    lv_qrcode_set_size(ui->screen_tickets_qrcode, 110);
    lv_qrcode_set_dark_color(ui->screen_tickets_qrcode, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->screen_tickets_qrcode, lv_color_hex(0xffffff));
    const char * screen_tickets_qrcode_data = "https://www.nxp.com/";
    lv_qrcode_update(ui->screen_tickets_qrcode, screen_tickets_qrcode_data, 20);

    //Write codes screen_tickets_btn_save_exit
    ui->screen_tickets_btn_save_exit = lv_button_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_btn_save_exit, 6, 180);
    lv_obj_set_size(ui->screen_tickets_btn_save_exit, 306, 43);
    ui->screen_tickets_btn_save_exit_label = lv_label_create(ui->screen_tickets_btn_save_exit);
    lv_label_set_text(ui->screen_tickets_btn_save_exit_label, "保存并退出");
    lv_label_set_long_mode(ui->screen_tickets_btn_save_exit_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_tickets_btn_save_exit_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_tickets_btn_save_exit, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_tickets_btn_save_exit_label, LV_PCT(100));

    //Write style for screen_tickets_btn_save_exit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_tickets_btn_save_exit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets_btn_save_exit, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets_btn_save_exit, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_tickets_btn_save_exit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_btn_save_exit, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_btn_save_exit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_btn_save_exit, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_btn_save_exit, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_btn_save_exit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_btn_save_exit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_progress_bar
    ui->screen_tickets_progress_bar = lv_bar_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_progress_bar, 6, 227);
    lv_obj_set_size(ui->screen_tickets_progress_bar, 306, 8);
    lv_obj_set_style_anim_duration(ui->screen_tickets_progress_bar, 1000, 0);
    lv_bar_set_mode(ui->screen_tickets_progress_bar, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_tickets_progress_bar, 0, 100);
    lv_bar_set_value(ui->screen_tickets_progress_bar, 50, LV_ANIM_OFF);

    //Write style for screen_tickets_progress_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_tickets_progress_bar, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets_progress_bar, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets_progress_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_progress_bar, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_progress_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_tickets_progress_bar, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_tickets_progress_bar, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets_progress_bar, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets_progress_bar, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_progress_bar, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_6
    ui->screen_tickets_label_6 = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_label_6, 40, 9);
    lv_obj_set_size(ui->screen_tickets_label_6, 186, 23);
    lv_label_set_text(ui->screen_tickets_label_6, "骑猪看风景....");
    lv_label_set_long_mode(ui->screen_tickets_label_6, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_6, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_6, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_1
    ui->screen_tickets_label_1 = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_label_1, 0, 54);
    lv_obj_set_size(ui->screen_tickets_label_1, 100, 32);
    lv_label_set_text(ui->screen_tickets_label_1, "获得彩票");
    lv_label_set_long_mode(ui->screen_tickets_label_1, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_1, &lv_font_NotoSansCJKscMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_2
    ui->screen_tickets_label_2 = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_label_2, 0, 95);
    lv_obj_set_size(ui->screen_tickets_label_2, 100, 32);
    lv_label_set_text(ui->screen_tickets_label_2, "已存彩票");
    lv_label_set_long_mode(ui->screen_tickets_label_2, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_2, &lv_font_NotoSansCJKscMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_3
    ui->screen_tickets_label_3 = lv_label_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_label_3, 0, 133);
    lv_obj_set_size(ui->screen_tickets_label_3, 100, 32);
    lv_label_set_text(ui->screen_tickets_label_3, "待存彩票");
    lv_label_set_long_mode(ui->screen_tickets_label_3, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_3, &lv_font_NotoSansCJKscMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_saving
    ui->screen_tickets_saving = lv_obj_create(ui->screen_tickets);
    lv_obj_set_pos(ui->screen_tickets_saving, 10, 70);
    lv_obj_set_size(ui->screen_tickets_saving, 300, 126);
    lv_obj_set_scrollbar_mode(ui->screen_tickets_saving, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->screen_tickets_saving, LV_OBJ_FLAG_HIDDEN);

    //Write style for screen_tickets_saving, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_saving, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_tickets_saving, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_tickets_saving, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_tickets_saving, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_saving, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_tickets_saving, lv_color_hex(0xf3f3f3), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_tickets_saving, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_saving, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_4
    ui->screen_tickets_label_4 = lv_label_create(ui->screen_tickets_saving);
    lv_obj_set_pos(ui->screen_tickets_label_4, 2, 14);
    lv_obj_set_size(ui->screen_tickets_label_4, 292, 61);
    lv_label_set_text(ui->screen_tickets_label_4, "自动保存中\n请稍候");
    lv_label_set_long_mode(ui->screen_tickets_label_4, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_4, &lv_font_NotoSansCJKscMedium_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_tickets_label_5
    ui->screen_tickets_label_5 = lv_label_create(ui->screen_tickets_saving);
    lv_obj_set_pos(ui->screen_tickets_label_5, 2, 82);
    lv_obj_set_size(ui->screen_tickets_label_5, 292, 32);
    lv_label_set_text(ui->screen_tickets_label_5, "每15秒自动上传保存");
    lv_label_set_long_mode(ui->screen_tickets_label_5, LV_LABEL_LONG_WRAP);

    //Write style for screen_tickets_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_tickets_label_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_tickets_label_5, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_tickets_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_tickets_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_tickets_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_tickets.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_tickets);

    //Init events for screen.
    events_init_screen_tickets(ui);
}
