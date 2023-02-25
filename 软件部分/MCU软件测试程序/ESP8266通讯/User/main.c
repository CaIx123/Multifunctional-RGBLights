#include "sys.h"
int main()
{
	delay_init();
	/*USART*/
	uart1_init(115200);		//串口-蓝牙
	uart2_init(115200);		//串口-WIFI模块
	/*TIM*/
	TIM3_Int_Init(7200-1,500-1);		//按键及对应的定时器
	TIM4_Int_Init(7200-1,1000-1);		//灯滚动频率	10Hz
	KEY_Init();
	Encoder_TIM2_Init();		//编码器接口初始化
	
	DATA_Pin_Init();		//WS2512数据线初始化
	
	Lcd_Init();		//显示屏初始化
	/*SPI*/
	SPI2_Init();		//W25Q64 Flash初始化
	W25QXX_Init();
	
	NVIC_Config();		//中断优先级设置
	
	LCD_Clear(WHITE);
	LCD_SetColor(WHITE,BLACK);
	
	Storage_Init();			//存储初始化
	LCD_Menu_Init();
	

	

	while(1)
	{
		if(MenuMode!=3)
		{
			LCD_Function();
			LCD_Switch();
			LCD_UpdateMenu();
			delay_ms(50);
		}
		if(MenuMode==3)
		{
			PicShow_Stroge();
		}
	}
}
