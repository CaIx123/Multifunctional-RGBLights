#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

extern uint8_t show_flag;
extern uint8_t DATABUFF[3200];
extern uint16_t Buff_count;
extern uint8_t data;

void uart1_init(u32 bound);					//????1?????????
void USART1_IRQHandler(void);     	//????1?§Ø???????
void USART1_Send_Data(char data);
void USART1_Send_String(char *String);
#endif	   


























