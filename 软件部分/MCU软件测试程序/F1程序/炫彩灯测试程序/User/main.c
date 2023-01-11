#include "sys.h"
int main()
{
	delay_init();
	uart1_init(115200);	
	
	KEY_Init();
	DATA_Pin_Init();
	Lcd_Init();
	Page_Init();
	SPI2_Init();
	W25QXX_Init();
	LCD_Clear(WHITE);
	while(1)
	{
	}
}
