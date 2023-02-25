#include "sys.h" 

/*
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority                       
  ============================================================================================================================
*/

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//4级抢占,4级响应。
	
	// 串口1（蓝牙）
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStruct);	
	
	//按键
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_Init(&NVIC_InitStruct);  //初始化NVIC寄存器
	//按键
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_Init(&NVIC_InitStruct);  //初始化NVIC寄存器
  // 串口2（ESP8266通讯）
	NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);	
}




























