#include <stdbool.h>
#include "sysvars.h"


/* vars 计数器 */
volatile uint32_t svCounterC = 0;   /* 投币计数 */
volatile uint32_t svCounterD = 0;   /* 出奖计数 */
volatile uint32_t svCounterW = 0;   /* 想要出票计数 */
volatile uint32_t svCounterR = 0;   /* 实际出票计数 */
volatile uint32_t svCounterE = 0;   /* 模拟彩票计数 */

/* vars 系统状态控制 */
uint8_t svDbgOn = 0;    		 /* 显示Debug信息 */
uint8_t svDbgCoin = 1;	    	 /* 显示彩票和投币debug信息 */
uint8_t svBooting = 1;		     /* 系统还在启动状态 */
uint8_t svTicketDirectOut = 0;   /* 当前是哪种出票模式 */
uint8_t svSignal = 0;            /* 信号强度 */
uint32_t svErrorFlag;		     /* 错误标志 */
uint32_t svErrorCount = 0;       /* 错误计数 */
char svServerConnected = 0;      /* 是否连接了服务器 */
short svPing;				     /* 心跳回应毫秒值 */
char svLastCommandExecuted[32] = {0};  /* 最后一次执行的命令的TS */

/* vars 系统设置信息 */
char svSystemID[32] = {0};       /* CHIP ID */
char svIMEI[20] = {0};           /* IMEI */
char svIMSI[20] = {0};           /* IMEI */
char svICCID[24] = {0};          /* ICCID */
uint8_t svDeviceType;            /* 1 标准，2 代替彩票机 */
uint8_t svCardDirection;	     /* 刷卡头开口方向, 1开口向上（默认选项），然后是向下，向左，向右 */
uint8_t svDeviceStatus;			 /* 设备状态 0 正常 1 未初始化 2 未绑定 */
char svUrlWXPay[256];			 /* 微信支付地址 */
char svUrlOta[256];			     /* 升级包地址 */

uint8_t svCoinSw2;		         /* 投币脉冲宽度 */
uint8_t svCoinPulseWidthInLow;	 /* COIN PIN脉冲宽度判断下限 */
uint8_t svCoinPulseWidthInHigh;	 /* COIN PIN脉冲宽度判断上限 */
uint8_t svPrizePulseWidthInLow;	 /* PRIZE PIN脉冲宽度判断下限 */
uint8_t svPrizePulseWidthInHigh; /* PRIZE PIN脉冲宽度判断上限 */
uint8_t svCoinPerPlay;			 /* 按键后一次投币数字 */
uint8_t svCoinPerPlay2;		     /* 按键后一次投币数字(第二按钮) */
uint8_t svTEpulse;               /* 模拟的彩票机 速度: 80ms per ticket, 12.5 TPS */

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
