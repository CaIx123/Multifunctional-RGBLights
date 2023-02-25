#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Pagedata
{
	uint8_t ChoiceNum;											//选项数目
	uint8_t CurrentChoice;													//选择数目
	uint8_t Str[4][10];											//待显示字符串
	const uint8_t ChoiceCN32x32[10][16*8];	//待显示汉字数组,第一维长度最大为10
};

extern uint8_t MenuUpdateFlag[4];

void LCD_Page_Reinit(uint16_t BackGronudColor,uint16_t RectColor,uint16_t StrColor);
void LCD_Menu_Init();

void LCD_ShowOutline();


void LCD_UpdareMenu();
/*菜单切换函数*/
void LCD_Switch();

void FunctionIn(uint8_t i,uint8_t j);

/*菜单功能函数*/
void Function1();
void Function2();
void Function3();
void Function4();

#endif
