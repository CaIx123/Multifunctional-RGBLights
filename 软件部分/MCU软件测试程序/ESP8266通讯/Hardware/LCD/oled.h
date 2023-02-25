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
#ifndef __OLED_H
#define __OLED_H			  	 
#include "sys.h"
#include "stdlib.h"	   
#include "stdint.h"	  
#define LCD_W 240
#define LCD_H 240

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	240
#define Max_Row		240
#define	Brightness	0xFF 
#define X_WIDTH 	240
#define Y_WIDTH 	240	    						  
//-----------------OLED端口定义----------------  					   
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_5)	//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_5)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_7)	//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOA,GPIO_Pin_7)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)		//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)		//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_1)
 		     
#define OLED_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//CS
#define OLED_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

extern  u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色

void Lcd_Init(void); 
void LCD_Clear(uint16_t Color);
void Address_set(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2);
void LCD_WR_DATA8(char da); //发送数据-8位参数
void LCD_WR_DATA(int da);
void LCD_WR_REG(char da);

void LCD_SetColor(uint16_t BACK,uint16_t WRITE);

void LCD_DrawPoint(uint16_t x,uint16_t y);//画点
void LCD_DrawPoint_big(uint16_t x,uint16_t y);//画一个大点
uint16_t  LCD_ReadPoint(uint16_t x,uint16_t y); //读点
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);		   
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);
void LCD_ShowChar(uint16_t x,uint16_t y,char ch,uint8_t mode);//显示一个字符
void LCD_ShowNum(uint16_t x,u16 y,u32 num,uint8_t len);//显示数字
void LCD_ShowSignedNum16(uint16_t x,u16 y,short int num,uint8_t len);	//显示16位的有符号数字
//void LCD_Show2Num(uint16_t x,u16 y,u16 num,uint8_t len);//显示2个数字
void LCD_ShowString(uint16_t x,u16 y,const char *p);		 //显示一个字符串,16字体

 
void LCD_Showimage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const unsigned char* image); 
void LCD_Showhanzi(uint16_t x,uint16_t y,uint16_t index,uint8_t Size);

/*注：x表示列，y表示行*/

					  		 
#endif  
	 
	 



