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



void setup_scr_screen_unbind(lv_ui *ui)
{
    //Write codes screen_unbind
    ui->screen_unbind = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_unbind, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_unbind, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_unbind, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_unbind, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind, lv_color_hex(0xf1fcfd), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_cont_1
    ui->screen_unbind_cont_1 = lv_obj_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_unbind_cont_1, 320, 36);
    lv_obj_set_scrollbar_mode(ui->screen_unbind_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_unbind_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_unbind_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind_cont_1, lv_color_hex(0xc5f0f5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_lb_device_id
    ui->screen_unbind_lb_device_id = lv_label_create(ui->screen_unbind_cont_1);
    lv_obj_set_pos(ui->screen_unbind_lb_device_id, 53, 8);
    lv_obj_set_size(ui->screen_unbind_lb_device_id, 252, 24);
    lv_label_set_text(ui->screen_unbind_lb_device_id, "SN: 12292202039302");
    lv_label_set_long_mode(ui->screen_unbind_lb_device_id, LV_LABEL_LONG_WRAP);

    //Write style for screen_unbind_lb_device_id, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_lb_device_id, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_lb_device_id, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_lb_device_id, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_lb_device_id, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_lb_device_id, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_qrcode
    ui->screen_unbind_qrcode = lv_qrcode_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_qrcode, 30, 50);
    lv_obj_set_size(ui->screen_unbind_qrcode, 140, 140);
    lv_qrcode_set_size(ui->screen_unbind_qrcode, 140);
    lv_qrcode_set_dark_color(ui->screen_unbind_qrcode, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->screen_unbind_qrcode, lv_color_hex(0xffffff));
    const char * screen_unbind_qrcode_data = "https://www.nxp.com/";
    lv_qrcode_update(ui->screen_unbind_qrcode, screen_unbind_qrcode_data, 20);

    //Write codes screen_unbind_btn_1
    ui->screen_unbind_btn_1 = lv_button_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_btn_1, 0, 0);
    lv_obj_set_size(ui->screen_unbind_btn_1, 30, 30);
    ui->screen_unbind_btn_1_label = lv_label_create(ui->screen_unbind_btn_1);
    lv_label_set_text(ui->screen_unbind_btn_1_label, "");
    lv_label_set_long_mode(ui->screen_unbind_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_unbind_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_unbind_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_unbind_btn_1_label, LV_PCT(100));

    //Write style for screen_unbind_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_unbind_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_unbind_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_btn_1, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_btn_2
    ui->screen_unbind_btn_2 = lv_button_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_btn_2, 290, 0);
    lv_obj_set_size(ui->screen_unbind_btn_2, 30, 30);
    ui->screen_unbind_btn_2_label = lv_label_create(ui->screen_unbind_btn_2);
    lv_label_set_text(ui->screen_unbind_btn_2_label, "");
    lv_label_set_long_mode(ui->screen_unbind_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_unbind_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_unbind_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_unbind_btn_2_label, LV_PCT(100));

    //Write style for screen_unbind_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_unbind_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_unbind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_btn_2, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_btn_3
    ui->screen_unbind_btn_3 = lv_button_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_btn_3, 290, 210);
    lv_obj_set_size(ui->screen_unbind_btn_3, 30, 30);
    ui->screen_unbind_btn_3_label = lv_label_create(ui->screen_unbind_btn_3);
    lv_label_set_text(ui->screen_unbind_btn_3_label, "");
    lv_label_set_long_mode(ui->screen_unbind_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_unbind_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_unbind_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_unbind_btn_3_label, LV_PCT(100));

    //Write style for screen_unbind_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_unbind_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_unbind_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_btn_3, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_btn_4
    ui->screen_unbind_btn_4 = lv_button_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_btn_4, 0, 210);
    lv_obj_set_size(ui->screen_unbind_btn_4, 30, 30);
    ui->screen_unbind_btn_4_label = lv_label_create(ui->screen_unbind_btn_4);
    lv_label_set_text(ui->screen_unbind_btn_4_label, "");
    lv_label_set_long_mode(ui->screen_unbind_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_unbind_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_unbind_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_unbind_btn_4_label, LV_PCT(100));

    //Write style for screen_unbind_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_unbind_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_unbind_btn_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_unbind_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_unbind_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_btn_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_btn_4, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_lbSignal
    ui->screen_unbind_lbSignal = lv_label_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_lbSignal, 45, 212);
    lv_obj_set_size(ui->screen_unbind_lbSignal, 231, 32);
    lv_label_set_text(ui->screen_unbind_lbSignal, "电信卡 | 信号强度 16");
    lv_label_set_long_mode(ui->screen_unbind_lbSignal, LV_LABEL_LONG_WRAP);

    //Write style for screen_unbind_lbSignal, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_lbSignal, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_lbSignal, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_lbSignal, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_lbSignal, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_lbSignal, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_unbind_label_1
    ui->screen_unbind_label_1 = lv_label_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_label_1, 183, 67);
    lv_obj_set_size(ui->screen_unbind_label_1, 114, 107);
    lv_label_set_text(ui->screen_unbind_label_1, "尚未初始化\n\n请用微信\n扫码绑定");
    lv_label_set_long_mode(ui->screen_unbind_label_1, LV_LABEL_LONG_WRAP);

    //Write style for screen_unbind_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_unbind_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_unbind_label_1, &lv_font_NotoSansCJKscMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_unbind_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_unbind_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_unbind_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_unbind.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_unbind);

    //Init events for screen.
    events_init_screen_unbind(ui);
}
