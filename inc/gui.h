#ifndef _GUI_H_
#define _GUI_H_

#include "mqttdata.h"
#include "../src/ui/gui_guider.h"

extern lv_ui ui;

void gui_init(void);
void gui_all_set_signal(bool ready, char *card, int signal);

/********************* UNBIND *********************/
void gui_unbind_switch(void);
void gui_unbind_set_sn(char *sn);

/********************* WAITING *********************/
void gui_waiting_switch(void);
void gui_waiting_set_machine(char *name);
void gui_waiting_set_comm_time(int second);
void gui_waiting_set_qrcode(wchar_t *sn);
void gui_waiting_set_coin(char coin);
void gui_waiting_set_signal(char *card, int signal);

/********************* TICKET *********************/
void gui_ticket_switch(void);
void gui_ticket_set_customer_info(WCustomer *info);
void gui_ticket_set_numbers(int got, int saved, int not_save);
void gui_ticket_end_timer(void);
void gui_ticket_update_save_timer(int countdown);
void gui_ticket_refresh_timer(void);
void gui_ticket_set_signal(char *card, int signal);

#endif
