#ifndef __RGB_LIGHT_H
#define __RGB_LIGHT_H	 
#include "sys.h" 

void DATA_Pin_Init(void);
void RGB_Send_1Code(void);
void RGB_Send_0Code(void);
void RGB_Reset(void);
void RGB_Send_1Bits(uint8_t Data);
void RGB_Send_24Bits(uint32_t Data);
void Send_RGBDATA(uint32_t Data);
void Send_RGB(uint8_t R,uint8_t G,uint8_t B);

#endif