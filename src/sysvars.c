﻿#include <stdbool.h>
#include "sysvars.h"


/* coiner pin, prize pin normal state */
GPIO_PinState svCoinerPinStateNormal = 1;
GPIO_PinState svPrizePinStateNormal = 1;

/* vars 计数器 */
volatile uint32_t svCounterC = 0;
volatile uint32_t svCounterD = 0;
volatile uint32_t svTicketIn = 0;	/* coin/doll counter, 插入彩票数字 */
volatile uint32_t svCoinInsert = 0; /* 模拟投币给主板个数, 给定时器使用。必须是2的倍数。每2表示投一次币 */

/* vars 系统状态控制 */
uint8_t svDeviceType = 0;   /* 0 标准，1 代替彩票机 */
uint8_t svDbgOn = 0;		/* 显示Debug信息 */
uint8_t svDbgCoin = 0;		/* 显示彩票和投币debug信息 */
uint8_t svBooting = 1;		/* 系统还在启动状态 */
uint32_t svErrorFlag;		/* 错误标志 */
char svServerConnected = 0; /* 是否连接了服务器 */
short svPing;				/* 心跳回应毫秒值 */

/* vars 系统设置信息 */
uint8_t svCardDirection;	     /* 刷卡头开口方向, 1开口向上（默认选项），然后是向下，向左，向右 */
uint8_t svDeviceStatus;			 /* 设备状态 0 正常 1 未初始化 2 未绑定 */
uint8_t svCoinPulseWidth;		 /* 投币脉冲宽度 */
uint8_t svCoinPulseWidthInLow;	 /* COIN PIN脉冲宽度判断下限 */
uint8_t svCoinPulseWidthInHigh;	 /* COIN PIN脉冲宽度判断上限 */
uint8_t svPrizePulseWidthInLow;	 /* PRIZE PIN脉冲宽度判断下限 */
uint8_t svPrizePulseWidthInHigh; /* PRIZE PIN脉冲宽度判断上限 */
uint8_t svCoinPerPlay;			 /* 按键后一次投币数字 */
uint8_t svCoinPerPlay2;		     /* 按键后一次投币数字(第二按钮) */
char svUrlWXPay[256];			 /* 微信支付地址 */

/* vars 下载图片数据及长宽 */
uint8_t svMerchantImage[24 * 24 * 6 / 8]; /* 商户名称点阵图，最大24像素6字 */
uint8_t svShopImage[24 * 24 * 9 / 8];	  /* 店铺名称点阵图，最大24像素9字 */
uint8_t svDeviceImage[20 * 20 * 11 / 8];  /* 设备名称点阵图，最大20像素11字 */
uint8_t svDeviceText[32];				  /* 设备名称GBK字符串，最大16字 */
uint16_t svMerchantImageWidth;
uint16_t svMerchantImageHeight;
uint16_t svShopImageWidth;
uint16_t svShopImageHeight;
uint16_t svDeviceImageWidth;
uint16_t svDeviceImageHeight;

/* 设备的Debug信息回报 */
uint32_t svDebugFlag = 0; /* bit0 : report valid pulse, bit 1: report invalid pulse */
uint32_t dbgPulseCoin;
uint32_t dbgPulsePrize;
char dbgPulseFromWhere;
char dbgPulseIsValid;
uint32_t svHack = 0;