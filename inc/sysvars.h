#ifndef _SYSTEM_VARIABLES_H_
#define _SYSTEM_VARIABLES_H_

#include <stdint.h>

#include "wrapper.h"

/* General Configs */
#define SYSTEM_NAME			"WWJNFC-401"
#define SOFTWARE_VERSION	1
#define HARDWARE_VERISON 	4
#define SUNNY_MAGIC_ID		0xFF12FF34
#define CONFIG_HACK_GAP_MIN		75

/* vars 计数器 */
extern volatile uint32_t svCounterC;
extern volatile uint32_t svCounterD;
extern volatile uint32_t svTicketIn;	/* coin/doll counter, 插入彩票数字 */
extern volatile uint32_t svCoinInsert; /* 模拟投币给主板个数, 给定时器使用。必须是2的倍数。每2表示投一次币 */

/* vars 系统状态控制 */
extern uint8_t svDbgOn;		/* 显示Debug信息 */
extern uint8_t svDbgCoin;		/* 显示彩票和投币debug信息 */
extern uint8_t svBooting;		/* 系统还在启动状态 */
extern uint32_t svErrorFlag;		/* 错误标志 */
extern char svServerConnected; /* 是否连接了服务器 */
extern short svPing;				/* 心跳回应毫秒值 */

/* vars 系统设置信息 */
extern char svSystemID[10];              /* Unique ID */
extern uint8_t svDeviceType;             /* 0 标准，1 代替彩票机 */
extern uint8_t svCardDirection;	         /* 刷卡头开口方向, 1开口向上（默认选项），然后是向下，向左，向右 */
extern uint8_t svDeviceStatus;			 /* 设备状态 0 正常 1 未初始化 2 未绑定 */
extern char svUrlWXPay[256];			 /* 微信支付地址 */
extern char svUrlOta[256];			     /* 升级包地址 */

extern uint8_t svCoinSw1;                /* 投币器电平，1，默认常开 */
extern uint8_t svCoinSw2;		         /* 投币脉冲宽度 */
extern uint8_t svCoinPulseWidthInLow ;	 /* COIN PIN脉冲宽度判断下限 */
extern uint8_t svCoinPulseWidthInHigh;	 /* COIN PIN脉冲宽度判断上限 */
extern uint8_t svPrizePulseWidthInLow;	 /* PRIZE PIN脉冲宽度判断下限 */
extern uint8_t svPrizePulseWidthInHigh;  /* PRIZE PIN脉冲宽度判断上限 */
extern uint8_t svCoinPerPlay;			 /* 按键后一次投币数字 */
extern uint8_t svCoinPerPlay2;			 /* 按键后一次投币数字(第二按钮) */

extern uint32_t svTEticketCount;         /* 模拟票数 */
extern uint8_t svTEpulse;                /* 80ms per ticket, 12.5 TPS */
extern uint8_t svTEsw1;                  /* Ticketer Emulator SW1: input polarity， def: 0 低电平开启 */
extern uint8_t svTEsw2;                  /* Ticketer Emulator SW2: output polarity， def: 0 常闭 */

/* vars 下载图片数据及长宽 */
extern uint8_t svMerchantImage[24 * 24 * 6 / 8]; /* 商户名称点阵图，最大24像素6字 */
extern uint8_t svShopImage[24 * 24 * 9 / 8];	  /* 店铺名称点阵图，最大24像素9字 */
extern uint8_t svDeviceImage[20 * 20 * 11 / 8];  /* 设备名称点阵图，最大20像素11字 */
extern uint8_t svDeviceText[32];				  /* 设备名称GBK字符串，最大16字 */
extern uint16_t svMerchantImageWidth;
extern uint16_t svMerchantImageHeight;
extern uint16_t svShopImageWidth;
extern uint16_t svShopImageHeight;
extern uint16_t svDeviceImageWidth;
extern uint16_t svDeviceImageHeight;

/* 设备的Debug信息回报 */
extern uint32_t svDebugFlag; /* bit0 : report valid pulse, bit 1: report invalid pulse */
extern uint32_t dbgPulseCoin;
extern uint32_t dbgPulsePrize;
extern char dbgPulseFromWhere;
extern char dbgPulseIsValid;
extern uint32_t svHack;

#endif
