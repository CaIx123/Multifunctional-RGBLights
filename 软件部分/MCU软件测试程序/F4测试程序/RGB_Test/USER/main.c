#include "sys.h"

#define R 0x00FF0000			//00R1R2G1G2B1B2
#define G 0x0000FF00			//00R1R2G1G2B1B2
#define B 0x000000FF			//00R1R2G1G2B1B2

int main()
{
	uint8_t i,j;
	delay_init(168);
	uart_init(115200);
	DATA_Pin_Init();
	delay_ms(20);
	while(1)
	{
		
//		Send_RGBDATA(R);
//		delay_ms(1000);
//		Send_RGBDATA(G);
//		delay_ms(1000);
//		Send_RGBDATA(B);
//		delay_ms(1000);
		//
//		Send_RGBDATA(RGB_SIGNAL);
		printf("OK,Data=%s",USART_RX_BUF);
		delay_ms(500);
//		Send_RGB(220,20,60);
//		delay_ms(500);
//		Send_RGB(255,0,255);
//		delay_ms(500);
//		Send_RGB(128,0,128);
//		delay_ms(500);
//		Send_RGB(138,43,226);
//		delay_ms(500);
//		Send_RGB(176,196,222);
//		delay_ms(500);
//		Send_RGB(112,128,144);
//		delay_ms(500);
//		Send_RGB(127,255,170);
//		delay_ms(500);
//		Send_RGB(250,250,210);
//		delay_ms(500);
	}
}
