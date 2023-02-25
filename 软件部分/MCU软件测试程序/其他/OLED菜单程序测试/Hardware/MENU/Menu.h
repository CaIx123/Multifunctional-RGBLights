#ifndef __MUNE_H
#define __MUNE_H
#include "stdint.h"

struct Page
{
	uint16_t BackGronudColor;								//页面背景颜色
	uint16_t RectColor;											//页面边框颜色
	uint8_t ChoiceNum;											//选择数目
	uint16_t CNColor;												//汉字颜色
	uint16_t CNRectColor;										//汉字框颜色
	const uint8_t ChoiceCN32x32[10][16*8];	//汉字数组,第一维长度最大为10
};

extern struct Page MenuPage[3];

void Page_Init();
void ShowPage(uint8_t PageNum);

#endif
