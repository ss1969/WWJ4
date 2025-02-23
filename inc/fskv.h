﻿#ifndef _NVRAM_H_
#define _NVRAM_H_

#include <stdint.h>
#include "luat_fskv.h"

#define FSKV_STRING_MAX_LEN          256
#define FSKV_SAVE_IMPORTANT_INTERVAL 1000

typedef enum _FSKV_ITEM {
    FSKV_EVT_COUNTER_C = 0,
    FSKV_EVT_COUNTER_D,
    FSKV_EVT_COUNTER_E,
    FSKV_EVT_COUNTER_R,
    FSKV_EVT_COUNTER_W,
    FSKV_EVT_COINER_SW2, /* output pulse width */
    FSKV_EVT_COIN_IN_LOW,
    FSKV_EVT_COIN_IN_HIGH,
    FSKV_EVT_TICKET_IN_LOW,
    FSKV_EVT_TICKET_IN_HIGH,
    FSKV_EVT_DEV_STATUS,
    FSKV_EVT_DEV_TYPE,
    FSKV_EVT_DEV_SCREEN_DIR,
    FSKV_EVT_COIN_PERPLAY_BTN1,
    FSKV_EVT_COIN_PERPLAY_BTN2,
    FSKV_EVT_TE_PULSE,

    FSKV_EVT_URL_WXPAY,

} FSKV_ITEM;

void fskv_reset_data(void);
void fskv_save_async(FSKV_ITEM item, uint32_t p1);
void fskv_task_init(void);
void fskv_deinit(void);

#endif
