#ifndef __WIFI_H
#define __WIFI_H			    
#include "sys.h" 
extern uint8_t show_flag;
extern uint8_t DATABUFF[4800];
extern uint16_t Buff_count;
extern uint8_t data;
extern uint8_t LastMode;
extern uint8_t WiFiName[10],IPAddress[16];
void PicShow_Stroge();

#endif
