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



void setup_scr_screen_watting(lv_ui *ui)
{
    //Write codes screen_watting
    ui->screen_watting = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_watting, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen_watting, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_watting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_watting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_watting, lv_color_hex(0xf2fbfc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_watting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_lb_coin
    ui->screen_watting_lb_coin = lv_label_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_lb_coin, 187, 69);
    lv_obj_set_size(ui->screen_watting_lb_coin, 114, 76);
    lv_label_set_text(ui->screen_watting_lb_coin, "80");
    lv_label_set_long_mode(ui->screen_watting_lb_coin, LV_LABEL_LONG_WRAP);

    //Write style for screen_watting_lb_coin, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_watting_lb_coin, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_watting_lb_coin, &lv_font_montserratMedium_80, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_watting_lb_coin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_watting_lb_coin, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_lb_coin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_label_3
    ui->screen_watting_label_3 = lv_label_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_label_3, 30, 210);
    lv_obj_set_size(ui->screen_watting_label_3, 167, 21);
    lv_label_set_text(ui->screen_watting_label_3, "扫码可投币、计票");
    lv_label_set_long_mode(ui->screen_watting_label_3, LV_LABEL_LONG_WRAP);

    //Write style for screen_watting_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_watting_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_watting_label_3, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_watting_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_watting_label_3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_cont_1
    ui->screen_watting_cont_1 = lv_obj_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_cont_1, 0, 0);
    lv_obj_set_size(ui->screen_watting_cont_1, 320, 36);
    lv_obj_set_scrollbar_mode(ui->screen_watting_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_watting_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_watting_cont_1, lv_color_hex(0xc5f0f5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_watting_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_qrcode
    ui->screen_watting_qrcode = lv_qrcode_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_qrcode, 30, 60);
    lv_obj_set_size(ui->screen_watting_qrcode, 140, 140);
    lv_qrcode_set_size(ui->screen_watting_qrcode, 140);
    lv_qrcode_set_dark_color(ui->screen_watting_qrcode, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->screen_watting_qrcode, lv_color_hex(0xffffff));
    const char * screen_watting_qrcode_data = "https://www.nxp.com/";
    lv_qrcode_update(ui->screen_watting_qrcode, screen_watting_qrcode_data, 20);

    //Write codes screen_watting_lb_time
    ui->screen_watting_lb_time = lv_label_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_lb_time, 230, 9);
    lv_obj_set_size(ui->screen_watting_lb_time, 78, 20);
    lv_label_set_text(ui->screen_watting_lb_time, "1min");
    lv_label_set_long_mode(ui->screen_watting_lb_time, LV_LABEL_LONG_WRAP);

    //Write style for screen_watting_lb_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_watting_lb_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_watting_lb_time, &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_watting_lb_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_watting_lb_time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_lb_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_label_4
    ui->screen_watting_label_4 = lv_label_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_label_4, 184, 159);
    lv_obj_set_size(ui->screen_watting_label_4, 120, 47);
    lv_label_set_text(ui->screen_watting_label_4, "币/局");
    lv_label_set_long_mode(ui->screen_watting_label_4, LV_LABEL_LONG_WRAP);

    //Write style for screen_watting_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_watting_label_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_watting_label_4, &lv_font_NotoSansCJKscMedium_36, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_watting_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_watting_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_watting_lb_machine
    ui->screen_watting_lb_machine = lv_label_create(ui->screen_watting);
    lv_obj_set_pos(ui->screen_watting_lb_machine, 17, 9);
    lv_obj_set_size(ui->screen_watting_lb_machine, 235, 21);
    lv_label_set_text(ui->screen_watting_lb_machine, "恐龙城堡 - 1号机");
    lv_label_set_long_mode(ui->screen_watting_lb_machine, LV_LABEL_LONG_WRAP);

    //Write style for screen_watting_lb_machine, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_watting_lb_machine, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_watting_lb_machine, &lv_font_NotoSansCJKscMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_watting_lb_machine, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_watting_lb_machine, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_watting_lb_machine, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_watting.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_watting);

}
