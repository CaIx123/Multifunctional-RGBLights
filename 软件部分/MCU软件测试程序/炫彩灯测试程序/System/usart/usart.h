#ifndef __USART_H
#define __USART_H
#include "sys.h"
#include "stdio.h"	 

void uart1_init(u32 bound);					
void USART1_IRQHandler(void);     	
void USART1_Send_Data(char data);
void USART1_Send_String(char *String);

void uart3_init(u32 bound);					
void USART3_IRQHandler(void);     	
void USART3_Send_Data(char data);
void USART3_Send_String(char *String);
#endif	   
