#ifndef  _ENCODER_H							
#define _ENCODER_H
#include "sys.h"

void Encoder_TIM2_Init(void);   // 编码器1初始化函数
void Encoder_TIM4_Init(void);   // 编码器2初始化函数
int Read_Speed(int TIMx);       // 编码器速度读取函数
void TIM2_IRQHandler(void);     // 定时器2中断服务函数
void TIM4_IRQHandler(void);     // 定时器4中断服务函数
#endif

