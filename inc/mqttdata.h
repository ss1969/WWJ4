#ifndef _MQTTDATA_H_
#define _MQTTDATA_H_

#include <stdio.h>
#include <string.h>
#include "defines.h"

typedef struct {
    int  firmwareVersion;
    char firmwareUrl[256];
    int  systemMode;
    char payUrl[256];
    int  coinPulseWidth;
    int  ticketPulseWidth;
    int  coinPulseLow;
    int  coinPulseHigh;
    int  ticketPulseLow;
    int  ticketPulseHigh;
    int  coinPerPlay;
    int  direction;
} WConfig;

typedef enum _SERVER_CMD_E { SVR_CMD_INSERT_COIN = 1, SVR_CMD_CLEAR_CNT, SVR_CMD_OUT_TICKET } SERVER_CMD;

typedef struct {
    char timeStamp[32];
    int  commandId;
    char commandParam[128];
} WCommand;

typedef struct {
    char userPortrait[256];
    char nickName[64];
    int  userID;
} WCustomer;

typedef struct {
    uint64_t timeStamp;
    int      hardwareVersion;
    int      firmwareVersion;
    char     imei[20];
    char     imsi[20];
    char     iccid[24];
    char     phone[24];
    int      signal;
    int      pinCoinerInit;
    int      pinMbOnoffInit;
    int      pinExtCountInit;
    int      errorCode;
    char     errorMessage[128];
} WStatusReport;

typedef struct {
    char dataFlag[DATA_FLAG_LENGTH * 2 + 1];
    char lastCommandTS[32];
    int  coin;
    int  prize;
    int  ticketWantOut;
    int  ticketRealOut;
    int  ticketEmulated;
} WCounterReport;

typedef struct {
    uint64_t timeStamp;
    int      userID;
    int      ticketAdd;
    int      ticketDirectOut;
} WTicketSave;

void mqtt_data_cb_config(char *data, uint32_t len);
void mqtt_data_cb_command(char *data, uint32_t len);
void mqtt_data_cb_customer(char *data, uint32_t len);
void mqtt_pub_status(int signal, char *imei, char *imsi, char *iccid, char *phone);
void mqtt_pub_counter(void);
void mqtt_pub_ticket_save(int userID, int ticketAdd, int ticketDirectOut);
void mqtt_pub_sms(char *time, char *phone, char *pdu);
void mqtt_data_free(void *obj);

void Testbench();

#endif
