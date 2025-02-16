#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#define MQTT_PUBACK_TIMEOUT 5000
#define MQTT_SSL            0 // 是否开启SSL
#define MQTT_AUTOCON        1 // 是否自动重连
#define MQTT_DEVICE_ID      svSystemID

int  mqtt_publish_data(char *topic, char *json, int qos);
void mqtt_task_init(const char *host, const int port, const char *username, const char *password);
void mqtt_task_deinit(void);

#endif