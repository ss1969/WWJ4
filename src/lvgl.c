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
#define LVGL_FLUSH_BUF_LINE 320

luat_rtos_task_handle lvgl_flush_task;
static int            wait_flush = 0;
static void          *draw_buf   = NULL;
static lv_indev_t    *indev_touchpad;
volatile bool         disp_flush_enabled = true;

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
    LUAT_DEBUG_ASSERT(draw_buf != NULL, "allocate lvgl buffer fail %dB",
                      LCD_WIDTH * LVGL_FLUSH_BUF_LINE * sizeof(lv_color_t));
    lv_display_set_buffers(disp, draw_buf, NULL, LCD_WIDTH * LVGL_FLUSH_BUF_LINE * sizeof(lv_color_t),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    /* below in lv_port_indev_template.c lv_port_indev_init() */
    tp_taskinit();
    indev_touchpad = lv_indev_create();
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);

    /* tick init */
    lv_tick_set_cb(soc_get_poweron_time_ms);

    /* own routine */
    lv_demo_widgets();
    // lv_demo_benchmark();

    while (true) {
        uint32_t t = lv_timer_handler();
        luat_rtos_task_sleep(t);
    }
}

void lvgl_taskinit(void) {
    luat_rtos_task_create(&lvgl_flush_task, 8 * 1024, 90, "lvgl", lvgl_main_routine, NULL, 16);
}
