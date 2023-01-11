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

#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
//u8 ref=0;//刷新显示
//u16 vx=15542,vy=11165;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
//u16 chx=140,chy=146;//默认像素点坐标为0时的AD起始值
void xianshi()//显示信息
{   
	u16 lx,ly;
	BACK_COLOR=BLUE;
	POINT_COLOR=RED;	
	LCD_Showhanzi(10,0,0,1);  //电
	LCD_Showhanzi(45,0,2,2);  //子

  LCD_ShowString(10,35,"1.3 IPS-SPI 240*320");
	LCD_ShowString(10,55,"LCD_W:");	LCD_ShowNum(70,55,LCD_W,3);
	LCD_ShowString(110,55,"LCD_H:");LCD_ShowNum(160,55,LCD_H,3);	
	lx=10;ly=75;			
}



void showimage() //显示40*40图片
{
	LCD_Showimage(60,120,40,40,image);
//	ref=0;				
}
 int main(void)
 {
		u8 t;
		delay_init();	    	 //延时函数初始化	  
		NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化

		Lcd_Init();			//初始化TFT
	
		LCD_Clear(WHITE); //清屏
		LCD_SetColor(WHITE,BLACK);

		xianshi(); //显示信息
    showimage(); //显示40*40图片


		while(1)
		{    
		}
}
