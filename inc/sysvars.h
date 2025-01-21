#ifndef _SYSTEM_VARIABLES_H_
#define _SYSTEM_VARIABLES_H_

#include <stdint.h>

#include "wrapper.h"

/* General Configs */
#define SYSTEM_NAME			"WWJ-780EP"
#define SOFTWARE_VERSION	1
#define HARDWARE_VERSION 	4
#define CONFIG_HACK_GAP_MIN		75

/* vars 计数器 */
extern volatile uint32_t svCounterC;
extern volatile uint32_t svCounterD;
extern volatile uint32_t svTicketIn;
extern volatile uint32_t svCounterW;
extern volatile uint32_t svCounterR;
extern volatile uint32_t svCounterE;

/* vars 系统状态控制 */
extern uint8_t svDbgOn;
extern uint8_t svDbgCoin;
extern uint8_t svBooting;
extern uint8_t svTicketDirectOut;
extern uint8_t svSignal;
extern uint32_t svErrorFlag;
extern uint32_t svErrorCount;
extern char svServerConnected;
extern short svPing;
extern char svLastCommandExecuted[32];  //k 未处理

/* vars 系统设置信息 */
extern char svSystemID[32];
extern char svIMEI[20];
extern char svIMSI[20];
extern char svICCID[24];
extern uint8_t svDeviceType;
extern uint8_t svCardDirection;
extern uint8_t svDeviceStatus;
extern char svUrlWXPay[256];
extern char svUrlOta[256];

extern uint8_t svCoinSw2;
extern uint8_t svCoinPulseWidthInLow ;
extern uint8_t svCoinPulseWidthInHigh;
extern uint8_t svPrizePulseWidthInLow;
extern uint8_t svPrizePulseWidthInHigh;
extern uint8_t svCoinPerPlay;
extern uint8_t svCoinPerPlay2;
extern uint8_t svTEpulse;

/* vars 下载图片数据及长宽 */
extern uint8_t svMerchantImage[24 * 24 * 6 / 8];
extern uint8_t svShopImage[24 * 24 * 9 / 8];
extern uint8_t svDeviceImage[20 * 20 * 11 / 8];
extern uint8_t svDeviceText[32];
extern uint16_t svMerchantImageWidth;
extern uint16_t svMerchantImageHeight;
extern uint16_t svShopImageWidth;
extern uint16_t svShopImageHeight;
extern uint16_t svDeviceImageWidth;
extern uint16_t svDeviceImageHeight;

/* 设备的Debug信息回报 */
extern uint32_t svDebugFlag;
extern uint32_t dbgPulseCoin;
extern uint32_t dbgPulsePrize;
extern char dbgPulseFromWhere;
extern char dbgPulseIsValid;
extern uint32_t svHack;

#endif
