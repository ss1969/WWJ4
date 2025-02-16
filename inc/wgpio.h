#ifndef _WWJ_GPIO_H_
#define _WWJ_GPIO_H_

#define PIN_BTN0           HAL_GPIO_33
#define PIN_COIN_IN        HAL_GPIO_35
#define PIN_COIN_OUT_HA    HAL_GPIO_37
#define PIN_COIN_OUT_LA    HAL_GPIO_38
#define PIN_COIN_OUT_WATCH HAL_GPIO_25
#define PIN_PRZ_MB_ONOFF   HAL_GPIO_34 // INPUT，接主板彩票口，开关；Mode1 不接，（PRZ_IN1）
#define PIN_PRZ_MB_COUNT   HAL_GPIO_27 // OUTPUT，接主板彩票口，计数；Mode1 不接（PRZ_OUT1）
#define PIN_PRZ_EXT_ONOFF  HAL_GPIO_23 // OUTOUT，接彩票机，Mode 1 不接（PRZ_OUT2）
#define PIN_PRZ_EXT_COUNT  HAL_GPIO_7  // INPUT，接彩票机或码表（PRZ_IN2）
#define PIN_LED_D0         HAL_GPIO_16
#define PIN_GPIO_16_ALT    4

void gpio_task_init(void);
void gpio_deinit(void);
int  gpio_toggle(int pin);
void gpio_led(bool on);
void gpio_outCoin(int count);
void gpio_outTicket(int count);
void gpio_setDirectOut(bool directOut);

#endif