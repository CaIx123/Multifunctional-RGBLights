#include "sys.h"
#include "bmp.h"
void Erase_All();
void test1();
void test2();
int main()
{
	delay_init();
	WS2812_DataPin_Init();
	Lcd_Init();
	W25QXX_Init();
	uart1_init(115200);
	LCD_Clear(BLACK);
	LCD_SetColor(BLACK,WHITE);
	
//	Erase_All();
	test2();
	while(1)
	{
		
	}
}
void Erase_All()
{
	LCD_ShowString(40,40,(const uint8_t *)"Start Erase");
	W25QXX_Erase_Chip();
	LCD_ShowString(40,40+20,(const uint8_t *)"OK");
}

/*测试1，先在扇区10写入40*40图像信息再读取显示*/
uint8_t	BUFF[3200];
void test1()
{
	LCD_ShowString(40,40,(const uint8_t *)"Start Test1");
	W25QXX_Write_Sector((u8*)image,10,3200,1);
	LCD_ShowString(40,40+20,(const uint8_t *)"Write Finished!");
	W25QXX_Read_Sector(BUFF,10,3200);
	LCD_ShowString(40,40+40,(const uint8_t *)"Read Finished!");
	LCD_ShowString(40,100,(const uint8_t *)"Image:");
	LCD_Showimage(40+8*10,100,40,40,BUFF);
}

uint8_t	im[3200]={0xAF};
void test2()
{
	LCD_ShowString(40,40,(const uint8_t *)"Start Test2");
//	W25QXX_Write_Sector((u8*)im,10,3200,1);
	LCD_ShowString(40,40+20,(const uint8_t *)"Write Finished!");
	W25QXX_Read_Sector(BUFF,10,3200);
	LCD_ShowString(40,40+40,(const uint8_t *)"Read Finished!");
	LCD_ShowString(40,100,(const uint8_t *)"Image:");
	LCD_Showimage(40+8*10,100,40,40,BUFF);
}
