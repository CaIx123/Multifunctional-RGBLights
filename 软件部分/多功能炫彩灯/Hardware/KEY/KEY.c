#include "KEY.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	LED=1;
} 


uint8_t Sure_Flag=0;
uint8_t Back_Flag=0;
uint8_t Uuup_Flag=0;
uint8_t Down_Flag=0;
void TIM3_IRQHandler(void)   //TIM3中断
{
	static int FLAG_KEY1[2]={0,0},FLAG_KEY2[2]={0,0};	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		/*定时器功能*/
		Encoder_Count=(short int)TIM_GetCounter(TIM2);
		if(Encoder_Count>=(short int)4)
		{
			Encoder_Count=0,Down_Flag=1;
			TIM_SetCounter(TIM2,0);
		}
		else if(Encoder_Count<=(short int)(-4))
		{
			Encoder_Count=0,Uuup_Flag=1;
			TIM_SetCounter(TIM2,0);
		}
		if(FLAG_KEY1[0]&&!KEY1)						FLAG_KEY1[1]=0;
		else if(FLAG_KEY1[0]&&KEY1)				FLAG_KEY1[1]=1;
		else if(KEY1)											FLAG_KEY1[0]=0;
		else															FLAG_KEY1[0]=1;
		
		if(FLAG_KEY2[0]&&!KEY2)						FLAG_KEY2[1]=0;
		else if(FLAG_KEY2[0]&&KEY2)				FLAG_KEY2[1]=1;
		else if(KEY2)											FLAG_KEY2[0]=0;
		else															FLAG_KEY2[0]=1;

		if(FLAG_KEY1[1])
		{
			FLAG_KEY1[0]=0;
			FLAG_KEY1[1]=0;
			Sure_Flag=1;
		}
		if(FLAG_KEY2[1])
		{
			FLAG_KEY2[0]=0;
			FLAG_KEY2[1]=0;
			Back_Flag=1;
		}
		
	}
		
}

