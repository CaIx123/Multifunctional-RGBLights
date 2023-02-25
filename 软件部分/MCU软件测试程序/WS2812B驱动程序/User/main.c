#include "sys.h"
//#define R 0x00FF0000			//00R1R2G1G2B1B2
//#define G 0x0000FF00			//00R1R2G1G2B1B2
//#define B 0x000000FF			//00R1R2G1G2B1B2
int main()
{
	delay_init();
	DATA_Pin_Init();
	OLED_Init();

	
	while(1)
	{
		 RGB_SETBE(4,10);
		Set_RGB1(200,0,0);
//		Set_RGB(10,20,50,40);
		Refresh_All();
		delay_ms(100);
	}
}
