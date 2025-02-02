/*
 * 如果使用PSRAM做缓存，可以不开低速模式
 * 跑分时不能用PSRAM做缓存，必须开低速模式，否则RAM不够
 */

#include "common_api.h"

#include "luat_base.h"
#include "luat_rtos.h"
#include "luat_mcu.h"
#include "luat_debug.h"

#include "lcd.h"
#include "ft6236.h"

#include "lvgl9\lvgl.h"
#include "lvgl9\demos\lv_demos.h"
#include "lvgl9\demos\widgets\lv_demo_widgets.h"
#define SPI_LCD_RAM_CACHE_MAX (LCD_WIDTH * LCD_HEIGHT)

#define LVGL_FLUSH_EVENT    1
#define LVGL_FLUSH_TIME     30
#define LVGL_FLUSH_BUF_LINE 32

luat_rtos_task_handle lvgl_flush_task;
luat_rtos_timer_t     lvgl_flush_timer;
luat_rtos_timer_t     lvgl_tick_timer;
static int            wait_flush = 0;
static void          *draw_buf;
static lv_indev_t    *indev_touchpad;
volatile bool         disp_flush_enabled = true;

static LUAT_RT_RET_TYPE lvgl_flush_timer_cb(LUAT_RT_CB_PARAM) {
    if (wait_flush < 2) {
        wait_flush++;
        luat_send_event_to_task(lvgl_flush_task, LVGL_FLUSH_EVENT, 0, 0, 0);
    }
}

static LUAT_RT_RET_TYPE lvgl_tick_timer_cb(LUAT_RT_CB_PARAM) {
    lv_tick_inc(1);
}

static void display_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
    if (disp_flush_enabled) {
        lcd_draw(area->x1, area->y1, area->x2, area->y2, (lv_color_t *)px_map);
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

static void touchpad_read(lv_indev_t *indev_drv, lv_indev_data_t *data) {
    static int32_t last_x = 0;
    static int32_t last_y = 0;

    /*Save the pressed coordinates and the state*/
    if (tp_is_pressed()) {
        tp_get_data(&last_x, &last_y);
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else {
        data->state = LV_INDEV_STATE_RELEASED;
    }

    /*Set the last pressed coordinates*/
    data->point.x = last_x;
    data->point.y = last_y;
}

#if LV_USE_LOG
void lv_log_print(lv_log_level_t level, const char *buf) {
    LUAT_DEBUG_PRINT("LV %d, %s", level, buf);
}
#endif

static void lvgl_main_routine(void *param) {
    luat_event_t event;

    lcd_init();
    lv_init();
#if LV_USE_LOG
    lv_log_register_print_cb(lv_log_print);
#endif

    /* below in lv_port_disp_template.c lv_port_indev_init() */
    lv_display_t *disp = lv_display_create(LCD_WIDTH, LCD_HEIGHT);
    lv_display_set_flush_cb(disp, display_flush);
    draw_buf = malloc(LCD_WIDTH * LVGL_FLUSH_BUF_LINE * sizeof(lv_color_t));
    lv_display_set_buffers(disp, draw_buf, NULL, LCD_WIDTH * LVGL_FLUSH_BUF_LINE, LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* below in lv_port_indev_template.c lv_port_indev_init() */
    tp_taskinit();
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

    /* flush timer  */
    luat_start_rtos_timer(lvgl_flush_timer, LVGL_FLUSH_TIME, 1);
    luat_start_rtos_timer(lvgl_tick_timer, 1, 1);
    lv_demo_widgets();
    // lv_demo_benchmark();

    while (true) {
        luat_wait_event_from_task(lvgl_flush_task, 0, &event, NULL, LUAT_WAIT_FOREVER);
        if (wait_flush)
            wait_flush--;
        lv_timer_handler();
    }
}

void lvgl_taskinit(void) {
    luat_rtos_task_create(&lvgl_flush_task, 8192, 90, "lvgl", lvgl_main_routine, NULL, 16);
    lvgl_flush_timer = luat_create_rtos_timer(lvgl_flush_timer_cb, NULL, NULL);
    lvgl_tick_timer  = luat_create_rtos_timer(lvgl_tick_timer_cb, NULL, NULL);
}

// INIT_TASK_EXPORT(lvgl_taskinit, "0");
