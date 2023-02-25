#ifndef __TIM_H
#define __TIM_H
#include "sys.h"

#define PWM_MAX 10000

void PWM_TIM1_Init(u16 Arr,u16 Psc);  //Psc:预分配值  Arr:重装值
void TIM3_Int_Init(u16 arr,u16 psc);

#endif