#include <stdbool.h>
#include <stdint.h>
#include <stdatomic.h>

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

/* vars */
static atomic_uint_fast32_t svCoinInsert; 			/* 模拟投币给主板个数, 给定时器使用。必须是2的倍数。每2表示投一次币 */
static atomic_uint_fast32_t svTEticketCount;        /* 模拟了多少票数 */
static atomic_uint_fast32_t svTKticketOut;          /* 要实际出多少票 */
static uint8_t coinSw1;               				/* 投币器SW1，直接从投币器读取而来 */
static uint8_t ticketerSw1;                 		/* 彩票机 出票信号 读取值 */
static uint8_t ticketerSw2;                 		/* 彩票机 计数信号 读取值*/



static void timer0_callback_coiner(void *param)
{
    if(svCoinInsert > 0){
		LUAT_DEBUG_PRINT("timer0_callback_coiner svCoinInsert=%d", svCoinInsert);
        gpio_toggle(PIN_COIN_OUT);
        gpio_toggle(PIN_PRZ_MB_COUNT);
        svCoinInsert --;
    }
}

static void timer0_callback_te(void *param)
{
    if(svCoinInsert > 0){
		LUAT_DEBUG_PRINT("timer0_callback_te svCoinInsert=%d", svCoinInsert);
        gpio_toggle(PIN_COIN_OUT);
        svCoinInsert --;
    }
}

static void timer1_callback_te(void *param)
{
	static char state = 0;
	if(state == 0){
		state = 1;
		luat_gpio_set(PIN_PRZ_MB_COUNT, !ticketerSw2);
		svTEticketCount ++;	// 写入单个edge即认为计数增加，因为主板会在单个edge后关掉onoff
	}
	else{
		state = 0;
		luat_gpio_set(PIN_PRZ_MB_COUNT, ticketerSw2);
	}
}

// 投币器信号输入
static void IrqHandlerCoin(void *data, void* args)
{
	static GPIO_PinState pps;
	static uint64_t tick;
	static uint8_t reportHackCnt = 0;
	GPIO_PinState ps = luat_gpio_get(PIN_COIN_IN);

	/* AIR780EP, prevent boot false irq interrupt */
	if(soc_get_poweron_time_tick() < MS2TICK(1000)) return;

	if(svDbgCoin) LUAT_DEBUG_PRINT("COIN PIN %s @ %dms", ps ? "UP" : "DOWN", TICK2MS(soc_get_poweron_time_tick()));

	/* we store the timestamp when FALLING. */
	if(ps != coinSw1){
		/* anti hack routine : check if last time is too small < 60ms */
		uint64_t lastGap = soc_get_poweron_time_tick() - tick;
		if(lastGap < MS2TICK(CONFIG_HACK_GAP_MIN)){
			svHack++;
			reportHackCnt++;
			if(reportHackCnt >= 3){
				//k CoinerNotifyHackDetected();
				reportHackCnt = 0;
			}
		}
		tick = soc_get_poweron_time_tick();
	}
	/* UPRISING after an falling. it's exiting the interrupt.
	We set detect limit to between 20~120ms  */
	else{
		if((pps != coinSw1) &&
		   (soc_get_poweron_time_tick() > MS2TICK(svCoinPulseWidthInLow) + tick) &&
		   (soc_get_poweron_time_tick() < MS2TICK(svCoinPulseWidthInHigh) + tick)){
			/* counter++, notify helper task */
			svCounterC++;

			//k CoinerNotifyCoinInsert();

			/* directly put 1 coin out, because gpio_outCoin() is very simple. */
			gpio_outCoin(1);

			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN++ %d, %dms", svCounterC, TICK2MS(soc_get_poweron_time_tick() - tick));
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("COIN DROP %dms", TICK2MS(soc_get_poweron_time_tick() - tick));
		}
	}

	/* store previous state */
	pps = ps;
}

// Mode1 出奖计数模式 PIN_PRZ_EXT_COUNT
static void IrqHandlerPrizeExtCntMode1(void *data, void* args)
{
	static GPIO_PinState pps;
	static volatile uint32_t tick;
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_EXT_COUNT);

	/* AIR780EP, prevent boot false irq interrupt */
	if(soc_get_poweron_time_tick() < MS2TICK(1000)) return;

	if(svDbgCoin) LUAT_DEBUG_PRINT("PIN_PRZ_EXT_COUNT %s @ %d", ps ? "UP" : "DOWN", TICK2MS(soc_get_poweron_time_tick()));

	/* we store the timestamp when FALLING. */
	if(ps != ticketerSw2){
		tick = soc_get_poweron_time_tick();
	}
	/* UPRISING after an falling. it's exiting the interrupt.
	high time/ low time:
	30ms/60ms, 98ms/49ms, for TL ticketer
	45/29 for another ticketer.
	We set detect limit to between 20~120ms  */
	else{
		if((pps != ticketerSw2) &&
		   (soc_get_poweron_time_tick() > MS2TICK(svPrizePulseWidthInLow) + tick) &&
		   (soc_get_poweron_time_tick() < MS2TICK(svPrizePulseWidthInHigh) + tick)){
			/* update coin per prize only if it's doll machine. */
			svCounterD++;

			//k if(svDeviceType == 1) CoinerNotifyCoinPerPrizeUpdate();

			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE++ %d, %dms", svCounterD, TICK2MS(soc_get_poweron_time_tick() - tick));
		}
		else{
			if(svDbgCoin) LUAT_DEBUG_PRINT("PRIZE DROP %dms", TICK2MS(soc_get_poweron_time_tick() - tick));
		}
	}

	/* store previous state */
	pps = ps;
}

// 彩票模式 PIN_PRZ_EXT_COUNT
static void IrqHandlerPrizeExtCntMode2(void *data, void* args)
{
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_EXT_COUNT);
	if(svDbgCoin) LUAT_DEBUG_PRINT("PIN_PRZ_EXT_COUNT STATE %s @ %dms", ps ? "HIGH" : "LOW", TICK2MS(soc_get_poweron_time_tick()));
	if(ps != ticketerSw2){
		svTKticketOut --;
		if(svTKticketOut == 0){
			// Turn OFF real ticketer
			luat_gpio_set(PIN_PRZ_EXT_ONOFF, !ticketerSw1);
		}
	}
}

// 彩票模式 PIN_PRZ_MB_ONOFF
static void IrqHandlerPrizeMBOnoffMode2(void *data, void* args)
{
	GPIO_PinState ps = luat_gpio_get(PIN_PRZ_MB_ONOFF);
	if(svDbgCoin) LUAT_DEBUG_PRINT("PIN_PRZ_MB_ONOFF STATE %s @ %dms", ps ? "HIGH" : "LOW", TICK2MS(soc_get_poweron_time_tick()));

	if(ps != ticketerSw1){	// start emulate
		svTEticketCount = 0;
		if(timer1) luat_rtos_timer_start(timer1, svTEpulse / 2, 1, timer1_callback_te, NULL);
	}
	else{	// stop emulate. 因为主板一般在收到单个edge就会关掉MB_ONOFF，所以手工把PIN_PRZ_MB_COUNT写inactive
		if(timer1) luat_rtos_timer_stop(timer1);
		luat_gpio_set(PIN_PRZ_MB_COUNT, ticketerSw2);
		LUAT_DEBUG_PRINT("TICKET EMULATED: %d tickets, timer %d", svTEticketCount);
	}
}

static void gpio_init(void)
{
	LUAT_DEBUG_ASSERT(svDeviceType == 1 || svDeviceType == 2, "sv device mode error %d", svDeviceType);
	LUAT_DEBUG_PRINT("gpio_init start, sys mode %d", svDeviceType);

    luat_gpio_cfg_t gpio_cfg;
    luat_gpio_set_default_cfg(&gpio_cfg);
    gpio_cfg.pull=Luat_GPIO_DEFAULT;

	// input irq pins
    gpio_cfg.mode=Luat_GPIO_IRQ;
    gpio_cfg.irq_type=LUAT_GPIO_BOTH_IRQ;

	// 投币器
    gpio_cfg.pin=PIN_COIN_IN;
	gpio_cfg.irq_cb=(void*)IrqHandlerCoin;
    luat_gpio_open(&gpio_cfg);

	// PIN_PRZ_EXT_COUNT
	gpio_cfg.pull = Luat_GPIO_PULLUP;	//k 以后应该去掉
    gpio_cfg.pin=PIN_PRZ_EXT_COUNT;
	if(svDeviceType == 1) gpio_cfg.irq_cb=(void*)IrqHandlerPrizeExtCntMode1;
	else if(svDeviceType == 2) gpio_cfg.irq_cb=(void*)IrqHandlerPrizeExtCntMode2;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pull=Luat_GPIO_DEFAULT;	//k 以后应该去掉

	// PIN_PRZ_MB_ONOFF （仅mode2）
	if(svDeviceType == 2) {
		gpio_cfg.pin=PIN_PRZ_MB_ONOFF;
		gpio_cfg.irq_cb=(void*)IrqHandlerPrizeMBOnoffMode2;
		luat_gpio_open(&gpio_cfg);
	}

	// output pins
    gpio_cfg.mode=LUAT_GPIO_OUTPUT;
    gpio_cfg.irq_type=LUAT_GPIO_NO_IRQ;
    gpio_cfg.pin=PIN_LED_D1;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_LED_D2;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_COIN_OUT;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_PRZ_MB_COUNT;
    luat_gpio_open(&gpio_cfg);
    gpio_cfg.pin=PIN_PRZ_EXT_ONOFF;
    luat_gpio_open(&gpio_cfg);

	// set defaults
	coinSw1 = luat_gpio_get(PIN_COIN_IN);				// 读取投币器输出值
	luat_gpio_set(PIN_COIN_OUT, coinSw1);

	// ticketerSw1 = luat_gpio_get(PIN_PRZ_MB_ONOFF);		// 读取主板彩票机开启信号值
	ticketerSw1 = 1;	//k
	luat_gpio_set(PIN_PRZ_EXT_ONOFF, ticketerSw1);

	ticketerSw2 = luat_gpio_get(PIN_PRZ_EXT_COUNT);		// 读取彩票机计数信号值
	luat_gpio_set(PIN_PRZ_MB_COUNT, ticketerSw2);

	LUAT_DEBUG_PRINT("gpio_init end");
}

void task_gpio(void)
{
    gpio_init();
    luat_rtos_timer_create(&timer0);
	if(svDeviceType == 1){
    	luat_rtos_timer_start(timer0, svCoinSw2, 1, timer0_callback_coiner, NULL);
		LUAT_DEBUG_PRINT("luat_rtos_timer_start timer0_callback_coiner %dms\n", svCoinSw2);
	}
	else if(svDeviceType == 2){
	    luat_rtos_timer_start(timer0, svTEpulse / 2, 1, timer0_callback_te, NULL);
		LUAT_DEBUG_PRINT("luat_rtos_timer_start timer0_callback_te %dms\n", svTEpulse / 2);
	    luat_rtos_timer_create(&timer1);
	}
}

void gpio_deinit(void)
{
	luat_rtos_task_suspend(task_gpio_handle);
	luat_rtos_task_delete(task_gpio_handle);

	luat_rtos_timer_stop(timer0);
	luat_rtos_timer_delete(timer0);
	luat_rtos_timer_stop(timer1);
	luat_rtos_timer_delete(timer1);

	luat_gpio_close(PIN_COIN_IN);
	luat_gpio_close(PIN_COIN_OUT);
	luat_gpio_close(PIN_PRZ_MB_ONOFF);
	luat_gpio_close(PIN_PRZ_MB_COUNT);
	luat_gpio_close(PIN_PRZ_EXT_COUNT);
	luat_gpio_close(PIN_PRZ_EXT_ONOFF);
	luat_gpio_close(PIN_LED_D1);
	luat_gpio_close(PIN_LED_D2);
}

int gpio_toggle(int pin)
{
    int r = luat_gpio_get(pin);
    r = r ? 0 : 1;
    luat_gpio_set(pin, r);
    return r;
}

void gpio_led(int id, bool on)
{
    if(id < 0 || id > 2)
        return;

    luat_gpio_set(id == 1 ? PIN_LED_D1 : PIN_LED_D2, on ? 1 : 0);
}

void gpio_set_coin_pulse_width(int widthMs)
{
    fskv_save_async(FSKV_EVT_COINER_SW2, widthMs);
    luat_rtos_timer_delete(timer0);
    luat_rtos_timer_create(&timer0);
    luat_rtos_timer_start(timer0, widthMs / 2, true, timer0_callback_coiner, NULL);
}

void gpio_outCoin(int count)
{
	svCoinInsert += count * 2;
}

void gpio_outTicket(int count)
{
	svTKticketOut += count;
	luat_gpio_set(PIN_PRZ_EXT_ONOFF, !ticketerSw1);	// Turn On real ticketer
}

uint32_t gpio_emuTicket(void)
{
	return svTEticketCount;
}
