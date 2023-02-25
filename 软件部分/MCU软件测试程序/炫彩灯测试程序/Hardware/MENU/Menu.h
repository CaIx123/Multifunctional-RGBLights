#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Pagedata
{
	uint8_t ChoiceNum;											//选项数目
	uint8_t CurrentChoice;									//选择数目
//	const uint8_t ChoiceCN32x32[10][16*8];	//待显示汉字数组,第一维长度最大为10
	char Str[4][10];									//待显示字符串
};

extern uint8_t MenuUpdateFlag[3];
extern uint8_t CurrentPage[2];		//菜单级数
extern uint8_t	MenuMode;
extern uint8_t NumGet;
void LCD_Page_Reinit(uint16_t BackGronudColor,uint16_t RectColor,uint16_t StrColor);

void LCD_Menu_Init();

void LCD_ShowOutline();

/*菜单更新函数*/
void LCD_UpdateChoice();
void LCD_UpdatePage(uint8_t CurrentPage0,uint8_t CurrentPage1);
void LCD_UpdateMenu();
/*菜单切换函数*/
void LCD_Switch();

void LCD_Function();

/*菜单功能函数*/
void Function1();
void Function2();
void Function3();
void Function4();

#endif
