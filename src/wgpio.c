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
#include "wgpio.h"

/* handles */
static luat_rtos_task_handle task_gpio_handle;
static luat_rtos_timer_t timer0;
static luat_rtos_timer_t timer1;


static int gpio_toggle(int pin)
{
    int r = luat_gpio_get(pin);
    r = r ? 0 : 1;
    luat_gpio_set(pin, r);
	LUAT_DEBUG_PRINT("set %d to %d", pin, r);
    return r;
}

static void coin_pin_pulse_gen(int count)
{
	if(svDbgCoin) LUAT_DEBUG_PRINT("coin_pin_pulse_gen %d", count);
	svCoinInsert += count * 2;
}

static void IrqHandlerAltPinCoiner(void *data, void* args)
{

}

/* called when pin interrupt. will filter too short pulses.
	FALLING - RISINIG suitable.
 */
static void IrqHandlerPrizePinCoiner(void *data, void* args)
{
	static GPIO_PinState pps;
	static volatile uint32_t tick;
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_IN);

	if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE PULSE %s @ %d", ps ? "UP" : "DOWN", soc_get_poweron_time_ms());

	/* we store the timestamp when FALLING. */
	if(ps != svPrizeNormal){
		tick = soc_get_poweron_time_ms();
	}
	/* UPRISING after an falling. it's exiting the interrupt.
	high time/ low time:
	30ms/60ms, 98ms/49ms, for TL ticketer
	45/29 for another ticketer.
	We set detect limit to between 20~120ms  */
	else{
		if((pps != svPrizeNormal) &&
		   (soc_get_poweron_time_ms() > svPrizePulseWidthInLow + tick) &&
		   (soc_get_poweron_time_ms() < svPrizePulseWidthInHigh + tick)){
			/* update coin per prize only if it's doll machine. */
			svCounterD++;

			//k if(svDeviceType == 1) CoinerNotifyCoinPerPrizeUpdate();

			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE++ %d, tik %d", svCounterD, soc_get_poweron_time_ms() - tick);
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE DROP tik %d", soc_get_poweron_time_ms() - tick);
		}
	}

	/* store previous state */
	pps = ps;
}

static void IrqHandlerCoinPin(void *data, void* args)
{
	static GPIO_PinState pps;
	static volatile uint32_t tick;
	static uint8_t reportHackCnt = 0;
	GPIO_PinState ps = luat_gpio_get(PIN_COIN_IN);

	if(svDbgCoin) LUAT_DEBUG_PRINT("COIN PULSE %s @ %devent.param1", ps ? "UP" : "DOWN", soc_get_poweron_time_ms());

	/* we store the timestamp when FALLING. */
	if(ps != svCoinNormal){
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
		if((pps != svCoinNormal) &&
		   (soc_get_poweron_time_ms() > svCoinPulseWidthInLow + tick) &&
		   (soc_get_poweron_time_ms() < svCoinPulseWidthInHigh + tick)){
			/* counter++, notify helper task */
			svCounterC++;

			//k CoinerNotifyCoinInsert();

			/* directly put 1 coin out, because coin_pin_pulse_gen() is very simple. */
			coin_pin_pulse_gen(1);

			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN++ %d, tik %devent.param1", svCounterC, soc_get_poweron_time_ms() - tick);
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN DROP tik %devent.param1", soc_get_poweron_time_ms() - tick);
		}
	}

	/* store previous state */
	pps = ps;
}

static void te_tm1_callback(void *param)
{
	static char state = 0;
	if(state == 0){
		state = 1;
		luat_gpio_set(PIN_PRZ_OUT, !svTEsw2);
	}
	else{
		state = 0;
		luat_gpio_set(PIN_PRZ_OUT, svTEsw2);
		svTEticketCount ++;
	}
}

static void IrqHandlerPrizePinTE(void *data, void* args)
{
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_IN);
	if(svDbgCoin) LUAT_DEBUG_PRINT("PRZ_IN STATE %s @ %devent.param1", ps ? "HIGH" : "LOW", soc_get_poweron_time_ms());

	if(svTEsw1 == ps){	// start emulate
		svTEticketCount = 0;
	    luat_rtos_timer_create(&timer1);
		luat_rtos_timer_start(timer1, svTEpulse / 2, 1, te_tm1_callback, NULL);
	}
	else{	// stop emulate
		luat_rtos_timer_stop(timer1);
		luat_rtos_timer_delete(timer1);
		LUAT_DEBUG_PRINT("TICKET EMULATED: %devent.param1", svTEticketCount);
	}
}

static void gpio_init(void)
{
	LUAT_DEBUG_PRINT("gpio_init start, sys mode %d", svDeviceType);

    luat_gpio_cfg_t gpio_cfg;
    luat_gpio_set_default_cfg(&gpio_cfg);
    gpio_cfg.pull=Luat_GPIO_DEFAULT;

	// input irq pins
    gpio_cfg.mode=Luat_GPIO_IRQ;
    gpio_cfg.irq_type=LUAT_GPIO_BOTH_IRQ;
	gpio_cfg.irq_cb=(void*)IrqHandlerPrizePinCoiner;
    gpio_cfg.pin=PIN_COIN_IN;
    luat_gpio_open(&gpio_cfg);
	gpio_cfg.irq_cb=(void*)IrqHandlerAltPinCoiner;
    gpio_cfg.pin=PIN_ALT_IN;
    luat_gpio_open(&gpio_cfg);
	if(svDeviceType == 0)
		gpio_cfg.irq_cb=(void*)IrqHandlerPrizePinCoiner;
	else if(svDeviceType == 1)
		gpio_cfg.irq_cb=(void*)IrqHandlerPrizePinTE;
    gpio_cfg.pin=PIN_PRZ_IN;
    luat_gpio_open(&gpio_cfg);

	// output pins
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

	// set defaults
	luat_gpio_set(PIN_COIN_OUT, svCoinNormal);
	luat_gpio_set(PIN_PRZ_OUT, svTEsw2);

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

static void timer_cb_coiner(void *param)
{
    if(svCoinInsert > 0){
		LUAT_DEBUG_PRINT("timer_cb_coiner svCoinInsert=%d", svCoinInsert);
        gpio_toggle(PIN_COIN_OUT);
        gpio_toggle(PIN_PRZ_OUT);
        svCoinInsert --;
    }
}

static void timer_cb_te(void *param)
{
    if(svCoinInsert > 0){
		LUAT_DEBUG_PRINT("timer_cb_te svCoinInsert=%d", svCoinInsert);
        gpio_toggle(PIN_COIN_OUT);
        svCoinInsert --;
    }
}

void update_coin_pulse(int widthMs)
{
    fskv_save_async(FSKV_EVT_COINER_PULSE, widthMs);
    luat_rtos_timer_delete(timer0);
    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, widthMs / 2, true, timer_cb_coiner, NULL);
}

void task_gpio(void)
{
    gpio_init();

    luat_rtos_timer_create(&timer0);
	if(svDeviceType == 0){
    	luat_rtos_timer_start(timer0, svCoinPulseWidth, 1, timer_cb_coiner, NULL);
		LUAT_DEBUG_PRINT("luat_rtos_timer_start timer_cb_coiner %dms\n", svCoinPulseWidth);
	}
	else if(svDeviceType == 1){
	    luat_rtos_timer_start(timer0, svTEpulse / 2, 1, timer_cb_te, NULL);
		LUAT_DEBUG_PRINT("luat_rtos_timer_start timer_cb_te %dms\n", svTEpulse / 2);
	}

    luat_rtos_task_create(&task_gpio_handle, 4*1024, 90, "task_gpio", gpio_main_routine, NULL, 0);
}

void gpio_deinit(void)
{
	luat_rtos_task_suspend(task_gpio_handle);
	luat_rtos_task_delete(task_gpio_handle);

	luat_rtos_timer_stop(timer0);
	luat_rtos_timer_delete(timer0);
	luat_rtos_timer_stop(timer1);
	luat_rtos_timer_delete(timer1);

	luat_gpio_close(PIN_ALT_IN  );
	luat_gpio_close(PIN_COIN_IN );
	luat_gpio_close(PIN_PRZ_IN  );
	luat_gpio_close(PIN_COIN_OUT);
	luat_gpio_close(PIN_PRZ_OUT );
	luat_gpio_close(PIN_SOCKET_3);
	luat_gpio_close(PIN_SOCKET_4);
	luat_gpio_close(PIN_LED_D1  );
	luat_gpio_close(PIN_LED_D2  );
}
