#ifndef _GUI_H_
#define _GUI_H_

#include "mqttdata.h"
#include "../src/ui/gui_guider.h"

extern lv_ui ui;

void gui_update_customer(WCustomer *info);
void gui_update_ticket_save(int countdown);
void gui_init(void);
#endif
