#ifndef _NVRAM_H_
#define _NVRAM_H_

#include <stdint.h>
#include "luat_fskv.h"

typedef enum _FSKV_ITEM
{
    FSKV_EVT_COUNTER_C = 0,
    FSKV_EVT_COUNTER_D,
    FSKV_EVT_COINER_PULSE,
    FSKV_EVT_COIN_IN_LOW,
    FSKV_EVT_COIN_IN_HIGH,
    FSKV_EVT_PRZ_IN_LOW,
    FSKV_EVT_PRZ_IN_HIGH,
    FSKV_EVT_DEV_STATUS,
    FSKV_EVT_DEV_TYPE,
    FSKV_EVT_DEV_DIR,
    FSKV_EVT_WX_URL,
    FSKV_EVT_COIN_BTN1,
    FSKV_EVT_COIN_BTN2
}FSKV_ITEM;

void fskv_init(void);
void fskv_save_async(FSKV_ITEM item, uint32_t p1);

#endif
