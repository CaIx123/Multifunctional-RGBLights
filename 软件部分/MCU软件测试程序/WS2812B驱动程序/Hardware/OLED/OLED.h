#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

void OLED_Init(void);

void OLED_ClearPart(void);
void OLED_ClearAll(void);
void OLED_Clear(uint8_t Line1, uint8_t Col1, uint8_t Line2, uint8_t Col2);

void OLED_SetTxitSize(uint8_t Size);

void OLED_SetData( uint8_t Data);
void OLED_WriteData(uint8_t Data);

void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_WriteCursor(uint8_t Y, uint8_t X);

void OLED_ShowPart(void);
void OLED_ShowAll(void);

void OLED_ShowChar(char Char);
void OLED_ShowString(char *String);
void OLED_ShowSignedNum(int32_t Number, uint8_t Length);
void OLED_ShowFloat(double real,uint8_t NN,uint8_t N);

//void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
//void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
//void OLED_ShowFloat(uint8_t Line,uint8_t Column,double real,uint8_t N);
//void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

//void OLED_DrawPicture(uint8_t Line, uint8_t Column, uint8_t Lenth, uint8_t Width, const uint8_t *String);				//Line 1~64    Col 1~128

/*不常用*/
//void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
//void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
/*待开发*/
//void OLED_ShowCN(uint8_t Line, uint8_t Column, char *String);						//待开发

#endif
