#ifndef _MQTTDATA_H_
#define _MQTTDATA_H_

#include <stdio.h>
#include <string.h>

typedef struct {
    int firmwareVersion;
    char firmwareUrl[100];
    char resourceUrl[100];
    int systemMode;
    char payUrl[100];
    char saveTicketUrl[100];
    int coinPulseWidth;
    int ticketPulseWidth;
    int coinPulseLow;
    int coinPulseHigh;
    int ticketPulseLow;
    int ticketPulseHigh;
    int coinPerPlay;
    int direction;
    int ticketDirectOut;
} MqttConfig;

typedef struct {
    uint64_t timeStamp;
    int commandId;
    char commandParam[128];
} Command;

typedef struct {
    int hardwareVersion;
    int firmwareVersion;
    char imei[20];
    char imsi[20];
    char iccid[24];
    char phone[24];
    int ticketDirectOut;
    int signal;
    int pinCoinerInit;
    int pinMbOnoffInit;
    int pinExtCountInit;
    int errorCode;
} StatusReport;

typedef struct {
    char lastCommandTS[20];
    int coin;
    int prize;
    int ticketWantOut;
    int ticketRealOut;
    int ticketEmulated;
} CounterReport;


void mqtt_data_cb_config(char* data, uint32_t len);
void mqtt_data_cb_command(char* data, uint32_t len);
void mqtt_pub_status(void);
void mqtt_pub_counter(void);
void mqtt_pub_sms(char* time, char* phone, char* pdu);
void mqtt_data_free(void *obj);

void Testbench();

#endif
