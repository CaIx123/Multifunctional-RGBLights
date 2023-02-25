/*
		编码器
		外设: TIM2,TIM4定时器
		引脚: TIM2: PA0 PA1
*/
#include "Encoder.h"
// 编码器1初始化函数
void Encoder_TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);  // 开启定时器时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE); // 开启GPIO时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // 浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   // 编码器1:PA0/PA1
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStruct);	
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;        // 不分频
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;    // 向上计数
  TIM_TimeBaseInitStruct.TIM_Period = 65535;                      // 重装载值65535
  TIM_TimeBaseInitStruct.TIM_Prescaler =0;                        // 分频系数0
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
  
  // 编码器配置函数: 定时器2，模式3，上升沿
  TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
  
  TIM_ICStructInit(&TIM_ICInitStruct);
  TIM_ICInitStruct.TIM_ICFilter = 10;       // 滤波器设置为10
  TIM_ICInit(TIM2,&TIM_ICInitStruct);
  
  TIM_ClearFlag(TIM2,TIM_FLAG_Update);      // 清除定时器标志位
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  // 定时器2，溢出更新，使能
  TIM_SetCounter(TIM2,0);                   // 定时数据清零
  TIM_Cmd(TIM2,ENABLE);                     // 定时器2使能
}

short int Encoder_Count=0;








