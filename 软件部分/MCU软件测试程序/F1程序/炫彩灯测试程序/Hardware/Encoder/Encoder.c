/*
		编码器
		外设: TIM2,TIM4定时器
		引脚: TIM2: PA0 PA1
					TIM4: PB7 PB6
*/
#include "Encoder.h"
#define LeftA_TIM2_PINA GPIO_Pin_0
#define LeftB_TIM2_PINA GPIO_Pin_1
#define RightA_TIM4_PINB GPIO_Pin_6
#define RightB_TIM4_PINB GPIO_Pin_7

int Encoder_Left,Encoder_Right; // 编码器数据（速度）
 
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

// 编码器2初始化函数
void Encoder_TIM4_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // 开启定时器时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); // 开启GPIO时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // 浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   // 编码器2:PB6/PB7
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB ,&GPIO_InitStruct);	
  
  TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // 不分频
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
  TIM_TimeBaseInitStruct.TIM_Period = 65535;                    // 重装载值65535
  TIM_TimeBaseInitStruct.TIM_Prescaler = 0;                     // 分频系数0
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
  
  // 编码器配置函数：定时器4，模式3，上升沿
  TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
  
  TIM_ICStructInit(&TIM_ICInitStruct);
  TIM_ICInitStruct.TIM_ICFilter = 10;       // 滤波器设置为10
  TIM_ICInit(TIM4,&TIM_ICInitStruct);
  
  TIM_ClearFlag(TIM4,TIM_FLAG_Update);      // 清除定时器溢出更新标志位
  TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  // 定时器4，溢出更新，使能
  TIM_SetCounter(TIM4,0);                   // 定时数据清零
  TIM_Cmd(TIM4,ENABLE);                     // 定时器2使能
}

// 编码器速度读取函数
// 入口参数：定时器
int Read_Speed(int TIMx)
{
  int value_1;
  switch(TIMx)
  {
    case 2:
      value_1 = (short)TIM_GetCounter(TIM2);  // 采集编码器的计数值并保存
      TIM_SetCounter(TIM2,0);   // 将定时器的计数值清零
      break;
    case 4:
      value_1 = (short)TIM_GetCounter(TIM4);  // 采集编码器的计数值并保存
      TIM_SetCounter(TIM4,0);   // 将定时器的计数值清零
      break; 
    default: value_1 = 0;
  }
  return value_1;
}

// 定时器2中断服务函数
void TIM2_IRQHandler()
{
  if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)  // 中断标志位置1
  {
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  // 清楚中断标志位
  }
}

// 定时器4中断服务函数
void TIM4_IRQHandler()
{
  if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)  // 中断标志位置1
  {
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  // 清楚中断标志位
  }
}





