/*
		串口通讯
		串口: USART1
		引脚: 
				RX	PA10
				TXPA9
*/

#include "usart.h"	  

#define RX1_PIN GPIO_Pin_10
#define TX1_PIN GPIO_Pin_9

#define RX2_PIN GPIO_Pin_3
#define TX2_PIN GPIO_Pin_2
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
	GPIO_InitStructure.GPIO_Pin=TX1_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=RX1_PIN;
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



uint8_t Data_OneByte=0;
uint8_t Data_Count=0,TransStartFlag=0;
uint8_t Data_Buff[6]={0};

void USART1_IRQHandler(void)                	
	{
	
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=0)  // 
  {
    Data_OneByte=USART_ReceiveData(USART1);     // 
		if(Data_OneByte==0xA5)TransStartFlag=1;
		if(TransStartFlag)
		{
			Data_Buff[Data_Count]=Data_OneByte;
			Data_Count++;
		}
		if(Data_OneByte==0x5A)
		{
			TransStartFlag=0,Data_Count=0;
			if((Data_Buff[1]&0x10)==0x10)NumGet=Data_Buff[2];
			else if((Data_Buff[1]&0x01)==0x01)Down_Flag=1;
			else if((Data_Buff[1]&0x02)==0x02)Sure_Flag=1;
			else if((Data_Buff[1]&0x04)==0x04)Back_Flag=1;
			else if((Data_Buff[1]&0x08)==0x08)Uuup_Flag=1;
		}
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
} 
	
void USART1_Send_Data(char data)
{
  USART_SendData(USART1,data);
  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);  // 
}


void USART1_Send_String(char *String)
{
  u16 len,j;
  len=strlen(String);
  for(j=0;j<len;j++)
  {
    USART1_Send_Data(*String++);
  }
}


void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能GPIOA时钟
	/* GPIO???? */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=TX2_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=RX2_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	/* USART???? */
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
}



