#ifndef _GUI_H_
#define _GUI_H_

#include "mqttdata.h"
#include "../src/ui/gui_guider.h"

extern lv_ui ui;

void gui_init(void);

void gui_unbind_switch(void);
void gui_unbind_set_sn(char *sn);
void gui_unbind_set_signal(char *card, int signal);

void gui_waiting_switch(void);

void gui_ticket_switch(void);
void gui_update_customer(WCustomer *info);
void gui_update_ticket_save(int countdown);

#endif
