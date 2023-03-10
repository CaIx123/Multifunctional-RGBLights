//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              CLK   接PA5（SCL）
//              MOSI   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1 
//							BLK  接A4 可以悬空
//							MISO 可以不接
//              ----------------------------------------------------------------
//******************************************************************************/

#include "sys.h"
#include "bmp.h"

 int main(void)
 {
		delay_init();	    	 //延时函数初始化	  
		uart1_init(115200);
		NVIC_Config();
	 
		Lcd_Init();			//初始化TFT
		LCD_Clear(WHITE); //清屏
		LCD_SetColor(WHITE,BLACK);
	 
		while(1)
		{
			if(MenuUpdateFlag[0])
			{
				LCD_ShowMenu();
				MenuUpdateFlag[0]=0;
			}
		}
}
