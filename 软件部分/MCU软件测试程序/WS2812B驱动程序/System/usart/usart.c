/*
		蓝牙串口通讯
		外设: USART3
		引脚: RX：P
					TX：P
*/

#include "usart.h"	  

#define RX_PIN GPIO_Pin_11
#define TX_PIN GPIO_Pin_10



//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch;      
	return ch;
}
#endif 


void uart3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	/* GPIO设置 */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=TX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=RX_PIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	/* USART设置 */
	USART_InitStructure.USART_BaudRate=bound;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART_InitStructure);
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
}



void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	uint8_t ch;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) ==1)
	{  	
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		ch =USART_ReceiveData(USART3);												//读取接收到的数据
		switch(ch)
		{
		}
		//USART_SendData(USART3 , ch); 													//把收到的数据发送回电脑	

	}
}
 
void USART3_Send_Data(char data)
{
  USART_SendData(USART3,data);
  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==0);  // 除非发送完成  
}

// 发送一串
void USART3_Send_String(char *String)
{
  u16 len,j;
  len=strlen(String);
  for(j=0;j<len;j++)
  {
    USART3_Send_Data(*String++);
  }
}

