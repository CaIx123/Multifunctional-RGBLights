#include "KEY.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	

} 


void TIM3_IRQHandler(void)   //TIM3中断
{
	
	static int count1=0,count2=0;
	static int FLAG_KEY1[2]={0,0},FLAG_KEY2[2]={0,0};	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
		if(!FLAG_KEY1[0]&&!FLAG_KEY1[1]&&KEY1)	count1++;
		else if(FLAG_KEY1[0]&&!KEY1)					FLAG_KEY1[1]=0;
		else if(FLAG_KEY1[0]&&KEY1)				FLAG_KEY1[1]=1;
		else if(KEY1)											FLAG_KEY1[0]=0;
		else																FLAG_KEY1[0]=1,count1=0;
		
		if(!FLAG_KEY2[0]&&!FLAG_KEY2[1]&&KEY2)	count2++;
		else if(FLAG_KEY2[0]&&!KEY2)					FLAG_KEY2[1]=0;
		else if(FLAG_KEY2[0]&&KEY2)				FLAG_KEY2[1]=1;
		else if(KEY2)											FLAG_KEY2[0]=0;
		else																FLAG_KEY2[0]=1,count2=0;


		if(count1>20)
		{
			count1=0;
		}
		if(count2>20)
		{
			count2=0;
		}
		if(FLAG_KEY1[1]&&count1<20)
		{

		}
		if(FLAG_KEY2[1]&&count2<20)
		{

		}
		
	}
		
}

