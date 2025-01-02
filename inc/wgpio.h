#ifndef _WWJ_GPIO_H_
#define _WWJ_GPIO_H_

#define PIN_COIN_IN         HAL_GPIO_6
#define PIN_COIN_OUT        HAL_GPIO_15
#define PIN_PRZ_MB_ONOFF    HAL_GPIO_3       // INPUT，接主板彩票口，开关；Mode1 不接
#define PIN_PRZ_MB_COUNT    HAL_GPIO_27      // OUTPUT，接主板彩票口，计数；Mode1 不接
#define PIN_PRZ_EXT_ONOFF   HAL_GPIO_14      // OUTOUT，接彩票机，Mode 1 不接 //k 15
#define PIN_PRZ_EXT_COUNT   HAL_GPIO_7       // INPUT，接彩票机或码表         //k 6

#define PIN_LED_D1      HAL_GPIO_26
#define PIN_LED_D2      HAL_GPIO_27

int gpio_toggle(int pin);
void gpio_led(int id, bool on);
void gpio_set_coin_pulse_width(int widthMs);
void gpio_outCoin(int count);
void gpio_outTicket(int count);
uint32_t gpio_emuTicket(void);


#endif