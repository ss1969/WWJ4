#ifndef _MOBILE_CTRL_H_
#define _MOBILE_CTRL_H_

typedef void (*net_status_callback)(bool ready);
typedef void (*net_sms_callback)(char *time, char *phone, char *pdu);
typedef void (*net_info_callback)(int signal, char *imei, char *imsi, char *iccid, char *phoneNumber);

void  mobile_task_init(void);
void  mobile_task_deinit(void);
void  mobile_set_netready_callback(net_status_callback cb);
void  mobile_set_sms_callback(net_sms_callback cb);
void  mobile_set_info_callback(net_info_callback cb);
char *mobile_detect_card(void);

#endif
