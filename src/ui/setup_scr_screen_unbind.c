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
    lv_obj_set_size(ui->screen_unbind_cont_1, 320, 37);
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
    lv_obj_set_pos(ui->screen_unbind_lb_device_id, 10, 10);
    lv_obj_set_size(ui->screen_unbind_lb_device_id, 252, 23);
    lv_label_set_text(ui->screen_unbind_lb_device_id, "SN：12292202039302");
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
    lv_obj_set_pos(ui->screen_unbind_qrcode, 21, 63);
    lv_obj_set_size(ui->screen_unbind_qrcode, 140, 140);
    lv_qrcode_set_size(ui->screen_unbind_qrcode, 140);
    lv_qrcode_set_dark_color(ui->screen_unbind_qrcode, lv_color_hex(0x2C3224));
    lv_qrcode_set_light_color(ui->screen_unbind_qrcode, lv_color_hex(0xffffff));
    const char * screen_unbind_qrcode_data = "https://www.nxp.com/";
    lv_qrcode_update(ui->screen_unbind_qrcode, screen_unbind_qrcode_data, 20);

    //Write codes screen_unbind_img_1
    ui->screen_unbind_img_1 = lv_image_create(ui->screen_unbind);
    lv_obj_set_pos(ui->screen_unbind_img_1, 174, 82);
    lv_obj_set_size(ui->screen_unbind_img_1, 128, 109);
    lv_obj_add_flag(ui->screen_unbind_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->screen_unbind_img_1, &_unbind1_RGB565A8_128x109);
    lv_image_set_pivot(ui->screen_unbind_img_1, 50,50);
    lv_image_set_rotation(ui->screen_unbind_img_1, 0);

    //Write style for screen_unbind_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->screen_unbind_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->screen_unbind_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_unbind.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_unbind);

}
