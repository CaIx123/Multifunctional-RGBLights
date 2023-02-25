#include "Menu.h"
#include "oled.h"

struct Page MenuPage[3];
void Page_Init()
{
	MenuPage[0].BackGronudColor=WHITE;
	MenuPage[0].RectColor=LIGHTBLUE;
}

void ShowPage(uint8_t PageNum)
{
	/*±³¾°É«*/
	LCD_Clear(MenuPage[PageNum].BackGronudColor);
	/*²Ëµ¥*/
	LCD_SetColor(MenuPage[PageNum].BackGronudColor,BLACK);
	LCD_Showhanzi(103-8,4,0,1);
	LCD_Showhanzi(103+16+8,4,1,1);
	/*»­±ß¿ò*/
	LCD_SetColor(MenuPage[PageNum].BackGronudColor,MenuPage[PageNum].RectColor);
	LCD_DrawRectangle(0,0,239,239);
	LCD_DrawRectangle(1,1,238,238);
	LCD_DrawLine(0,24,239,24);
	LCD_DrawLine(0,25,239,25);
	LCD_DrawLine(103-10,0,103-10,23);
	LCD_DrawLine(103+32+10,0,103+32+10,23);
	LCD_DrawLine(103-11,0,103-11,23);
	LCD_DrawLine(103+32+11,0,103+32+11,23);
	/*ÏÔÊ¾ºº×Ö*/
	
}

void ShowCouser(uint8_t	ChoiceNum)
{
	
}
