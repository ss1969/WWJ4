#include <stdbool.h>
#include <stdint.h>

#include "common_api.h"

#include "luat_rtos.h" //luat 头文件 封装FreeRTOS
#include "luat_debug.h"//luat DBUG 库
#include "luat_gpio.h"//luat GPIO 库
#include "luat_timer.h"
#include "platform_define.h"
#include "pad.h"
#include "luat_pm.h"

#include "wrapper.h"
#include "sysvars.h"
#include "fskv.h"
#include "usart.h"


#define PIN_ALT_IN      HAL_GPIO_3
#define PIN_COIN_IN     HAL_GPIO_6
#define PIN_PRZ_IN      HAL_GPIO_7
#define PIN_COIN_OUT    HAL_GPIO_15
#define PIN_PRZ_OUT     HAL_GPIO_14
#define PIN_SOCKET_3    HAL_GPIO_4
#define PIN_SOCKET_4    HAL_GPIO_5
#define PIN_LED_D1      HAL_GPIO_26
#define PIN_LED_D2      HAL_GPIO_27


/* handles */
luat_rtos_task_handle task_gpio_handle;
luat_rtos_timer_t timer0;
luat_rtos_timer_t timer1;



void CoinerGeneratePulse(int count)
{
	svCoinInsert += count * 2;
}


/* called when pin interrupt. will filter too short pulses.
	FALLING - RISINIG suitable.
 */
void CoinerPinPulseFilterPrize(void)
{
	static GPIO_PinState pps;
	static volatile uint32_t tick;
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_IN);

	if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE PULSE %s @ %d\n", ps ? "UP" : "DOWN", soc_get_poweron_time_ms());

	/* we store the timestamp when FALLING. */
	if(ps != svPrizePinStateNormal){
		tick = soc_get_poweron_time_ms();
	}
	/* UPRISING after an falling. it's exiting the interrupt.
	high time/ low time:
	30ms/60ms, 98ms/49ms, for TL ticketer
	45/29 for another ticketer.
	We set detect limit to between 20~120ms  */
	else{
		if((pps != svPrizePinStateNormal) &&
		   (soc_get_poweron_time_ms() > svPrizePulseWidthInLow + tick) &&
		   (soc_get_poweron_time_ms() < svPrizePulseWidthInHigh + tick)){
			svCounterD++;

			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE++ %d, tik %d\n", svCounterD, soc_get_poweron_time_ms() - tick);

			/* update coin per prize only if it's doll machine. */
			//k if(svDeviceType == 1) CoinerNotifyCoinPerPrizeUpdate();

			/* save to flash */
			fskv_save_async(FSKV_EVT_COUNTER_D, NULL);
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE DROP tik %d\n", soc_get_poweron_time_ms() - tick);
		}
	}

	/* store previous state */
	pps = ps;
}

void CoinerPinPulseFilterCoin(void)
{
	static GPIO_PinState pps;
	static volatile uint32_t tick;
	static uint8_t reportHackCnt = 0;
	GPIO_PinState ps = luat_gpio_get(PIN_COIN_IN);

	if(svDbgCoin) LUAT_DEBUG_PRINT("COIN PULSE %s @ %d\n", ps ? "UP" : "DOWN", soc_get_poweron_time_ms());

	/* we store the timestamp when FALLING. */
	if(ps != svCoinerPinStateNormal){
		/* anti hack routine : check if last time is too small < 60ms */
		uint32_t lastGap = soc_get_poweron_time_ms() - tick;
		if(lastGap < CONFIG_HACK_GAP_MIN){
			svHack++;
			reportHackCnt++;
			if(reportHackCnt >= 3){
				//k CoinerNotifyHackDetected();
				reportHackCnt = 0;
			}
		}
		tick = soc_get_poweron_time_ms();
	}
	/* UPRISING after an falling. it's exiting the interrupt.
	We set detect limit to between 20~120ms  */
	else{
		if((pps != svCoinerPinStateNormal) &&
		   (soc_get_poweron_time_ms() > svCoinPulseWidthInLow + tick) &&
		   (soc_get_poweron_time_ms() < svCoinPulseWidthInHigh + tick)){
			/* counter++, notify helper task */
			svCounterC++;
			//k CoinerNotifyCoinInsert();

			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN++ %d, tik %d\n", svCounterC, soc_get_poweron_time_ms() - tick);

			/* directly put 1 coin out, because CoinerGeneratePulse() is very simple. */
			CoinerGeneratePulse(1);

			/* save to flash */
			fskv_save_async(FSKV_EVT_COUNTER_C, NULL);
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN DROP tik %d\n", soc_get_poweron_time_ms() - tick);
		}
	}

	/* store previous state */
	pps = ps;
}


void gpio_level_irq(void *data, void* args)
{
    switch((int)data){
        case PIN_ALT_IN:
            break;
        case PIN_COIN_IN:
            CoinerPinPulseFilterCoin();
            break;
        case PIN_PRZ_IN:
			CoinerPinPulseFilterPrize();
            break;
    }
}

void gpio_init(void)
{
	LUAT_DEBUG_PRINT("gpio_init start");

    luat_gpio_cfg_t gpio_cfg;
    luat_gpio_set_default_cfg(&gpio_cfg);
    gpio_cfg.pull=Luat_GPIO_DEFAULT;
    gpio_cfg.mode=Luat_GPIO_IRQ;
    gpio_cfg.irq_type=LUAT_GPIO_BOTH_IRQ;
    gpio_cfg.irq_cb=(void*)gpio_level_irq;

    gpio_cfg.pin=PIN_ALT_IN;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_COIN_IN;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_PRZ_IN;
    luat_gpio_open(&gpio_cfg);

    gpio_cfg.mode=LUAT_GPIO_OUTPUT;
    gpio_cfg.irq_type=LUAT_GPIO_NO_IRQ;
    gpio_cfg.pin=PIN_LED_D1;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_LED_D2;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_COIN_OUT;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_PRZ_OUT;
    luat_gpio_open(&gpio_cfg);

	LUAT_DEBUG_PRINT("gpio_init end");
}

static void gpio_main_routine(void *param)
{
    while (1)
    {
        luat_gpio_set(PIN_LED_D1,0);
        luat_rtos_task_sleep(1000);
        luat_gpio_set(PIN_LED_D1,1);
        luat_rtos_task_sleep(1000);
    }
}

static void gpio_led(int id, bool on)
{
    if(id < 0 || id > 2)
        return;

    luat_gpio_set(id == 1 ? PIN_LED_D1 : PIN_LED_D2, on ? 1 : 0);
}

static int gpio_toggle(int pin)
{
    int r = luat_gpio_get(pin);
    r = r ? 0 : 1;
    luat_gpio_set(pin, r);
    return r;
}


static void timer0_callback(void *param)
{
	// luat_rtos_semaphore_release(g_http_task_semaphore_handle);
    if(svCoinInsert > 0){
        gpio_toggle(PIN_COIN_OUT);
        gpio_toggle(PIN_PRZ_OUT);
        svCoinInsert --;
    }
}

static void timer1_callback(void *param)
{
	// luat_rtos_semaphore_release(g_http_task_semaphore_handle);
}

void update_coin_pulse(int widthMs)
{
    fskv_save_async(FSKV_EVT_COINER_PULSE, widthMs);
    luat_rtos_timer_delete(timer0);
    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, widthMs / 2, true, timer0_callback, NULL);
}

void task_gpio(void)
{
    gpio_init();

    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, svCoinPulseWidth / 2, 1, timer0_callback, NULL);
    luat_rtos_timer_create(&timer1);
    luat_rtos_timer_start(timer1, 40, 1, timer1_callback, NULL);

    luat_rtos_task_create(&task_gpio_handle, 4*1024, 50, "task_gpio", gpio_main_routine, NULL, 0);
}

