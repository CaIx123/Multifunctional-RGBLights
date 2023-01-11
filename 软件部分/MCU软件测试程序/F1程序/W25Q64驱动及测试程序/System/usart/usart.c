/*
		??????????
		????: USART1
		????: RX??PA10
					TX??PA9
*/

#include "usart.h"	  

#define RX_PIN GPIO_Pin_10
#define TX_PIN GPIO_Pin_9
//????????????,???printf????,??????????use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//????????????????                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//????_sys_exit()???????e???????    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//?????fputc???? 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//???????,??????????   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

void uart1_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	/* GPIO???? */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=TX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=RX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* USART???? */
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
}


uint8_t DATABUFF[3200];
uint16_t Buff_count=0;
uint8_t show_flag=0;
uint8_t data=0;

void USART1_IRQHandler(void)                	//????1??????????
	{
	
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=0)  // ????????????????
  {
    data=USART_ReceiveData(USART1);     // ?????????????
		DATABUFF[Buff_count]=data;
		Buff_count++;
		
		if(Buff_count>=3200)
		{
			Buff_count=0;
			show_flag=1;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
} 
	
void USART1_Send_Data(char data)
{
  USART_SendData(USART1,data);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);  // ??????????  
}

// ???????
void USART1_Send_String(char *String)
{
  u16 len,j;
  len=strlen(String);
  for(j=0;j<len;j++)
  {
    USART1_Send_Data(*String++);
  }
}



