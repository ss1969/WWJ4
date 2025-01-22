#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#define MQTT_PUBACK_TIMEOUT 5000
#define MQTT_SSL			0			// 是否开启SSL
#define MQTT_AUTOCON		1			// 是否自动重连
#define MQTT_DEVICE_ID		svSystemID

void mqtt_update_reconnect(const char *host, int port, const char *username, const char *password);
int mqtt_publish_data(char* topic, char *json, int qos);
void mqtt_taskinit(void);
void mqtt_deinit(void);

#endif