#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

void uart1_init(u32 bound);					//????1?????????
void uart2_init(u32 bound);
void USART1_Send_Data(char data);
void USART1_Send_String(char *String);
#endif	   
