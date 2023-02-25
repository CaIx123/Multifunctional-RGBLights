#include "sys.h"
int main()
{
	delay_init();
	uart1_init(115200);		//串口-蓝牙
	//uart3_init(115200);		//串口-WIFI模块
	
	TIM3_Int_Init(7200-1,500-1);		//按键及对应的定时器
	KEY_Init();
	Encoder_TIM2_Init();		//编码器接口初始化
	
	DATA_Pin_Init();		//WS2512数据线初始化
	
	Lcd_Init();		//显示屏初始化

	SPI2_Init();		//W25Q64 Flash初始化
	W25QXX_Init();
	
	NVIC_Config();		//中断设置
	
	LCD_Clear(WHITE);
	LCD_SetColor(WHITE,BLACK);
	
	LCD_Menu_Init();
	
	Storage_Init();			//存储初始化
	
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
		}
	}
}
