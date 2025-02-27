#ifndef _MOBILE_CTRL_H_
#define _MOBILE_CTRL_H_

typedef void (*net_status_callback)(bool ready);
typedef void (*net_sms_callback)(char *time, char *phone, char *pdu);
typedef void (*net_info_callback)();

void mobile_task_init(void);
void mobile_task_deinit(void);

void  mobile_set_netready_callback(net_status_callback cb);
void  mobile_set_sms_callback(net_sms_callback cb);
void  mobile_set_info_callback(net_info_callback cb);
char *mobile_detect_card(void);
void  mobile_set_sn(char *newSn);
void  mobile_get_muid(void);
void  mobile_get_band(void);
void  mobile_get_cell_info(void);
void  mobile_get_status(bool *ready, uint8_t *signal, char **imei, char **imsi, char **iccid, char **phoneNumber);

#endif
