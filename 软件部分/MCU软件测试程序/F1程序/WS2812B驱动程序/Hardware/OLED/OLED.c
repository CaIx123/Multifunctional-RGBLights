/*
		OLED显示屏驱动，IIC通讯
		外设: 无特殊
		引脚: SCL：PB8
					SDA：PB9
*/

#include "sys.h"
#include "OLED_Font.h"
#include "stm32f10x.h"
#include "string.h"

/*引脚配置*/
#define OLED_PINB_SCL GPIO_Pin_8
#define OLED_PINB_SDA GPIO_Pin_9
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, OLED_PINB_SCL, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, OLED_PINB_SDA, (BitAction)(x))

uint8_t NumSize=1;
uint8_t PicStr[8][128]={0x00};
uint16_t Line0=1,Col0=1;
uint16_t Line=1,Col=1;
uint8_t del=0;
 
/*引脚初始化*/
void OLED_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitSt;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 	GPIO_InitSt.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitSt.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitSt.GPIO_Pin = OLED_PINB_SCL;
 	GPIO_Init(GPIOB, &GPIO_InitSt);
	GPIO_InitSt.GPIO_Pin = OLED_PINB_SDA;
 	GPIO_Init(GPIOB, &GPIO_InitSt);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}


void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}


void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}


void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

void OLED_SetTxitSize(uint8_t Size)
{
	NumSize=Size;
}

void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	Line0=Y;Col0=X;Line=Y;Col=X;
}


void OLED_WriteCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | (Y-1));												//设置Y位置
	OLED_WriteCommand(0x10 | ((X-1& 0xF0) >> 4));				//设置X位置低4位
	OLED_WriteCommand(0x00 | (X-1 & 0x0F));								//设置X位置高4位
}

void OLED_SetData( uint8_t Data)
{
	PicStr[Line-1][Col-1]=Data;
	Col++;
	if(Col>128)
	{
		Col=1;
		Line+=NumSize;
		if(Line>8-del)
		{
			Line=1;
		}
	}
}

void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

void OLED_ShowPart()
{
	uint16_t i,j;
	for(i=Line0,j=Col0;i!=Line+1+del&&j!=Col;i++)
	{
		OLED_WriteCursor(i, j==Col0?Col0:j);
		for(;j<Col||(i!=Line&&j<=128);j++)
		{
			OLED_WriteData(PicStr[i-1][j-1]);
		}
		j=1;
		if(i>=8)
		{
			i=0;
		}
	}
}

void OLED_ShowAll(void)
{
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_WriteCursor(j+1, 1);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(PicStr[j][i]);
		}
	}
}

void OLED_ClearPart(void)
{
	uint16_t i,j;
	for(i=Line0,j=Col0;i!=Line+1+del&&j!=Col;i++)
	{
		OLED_WriteCursor(i, j==Col0?Col0:j);
		for(;j<Col||(i!=Line&&j<=128);j++)
		{
			OLED_WriteData(0x00);
		}
		j=1;
		if(i>=8)
		{
			i=0;
		}
	}
}

void OLED_ClearAll(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_WriteCursor(j+1, 1);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

void OLED_Clear(uint8_t Line1, uint8_t Col1, uint8_t Line2, uint8_t Col2)
{
	uint16_t i,j;
	for(i=Line1,j=Col1;i<=Line2;i++)
	{
		OLED_WriteCursor(i, j==Col1?Col1:j);
		for(;j<Col2||(i!=Line2&&j<=128);j++)
		{
			OLED_WriteData(0x00);
		}
		j=1;
		if(i>=8)
		{
			i=0;
		}
	}
}

void OLED_ShowChar(char Char)
{      	
	uint8_t i;
	if(NumSize==1)
	{
		//if(Col>123)
		//{
		//	Col=128;OLED_SetData(0x00);
		//}
		for(i=0;i<6;i++)
		{
			OLED_SetData(OLED_F6x8[Char - ' '][i]);							//显示内容
		}
	}
	else if(NumSize==2)
	{
		del=1;
		//if(Col>121)
		//{
		//	Col=128;OLED_SetData(0x00);
		//}
		for (i = 0; i < 8; i++)
		{
			OLED_SetData(OLED_F8x16[Char - ' '][i]);						//显示上半部分内容
		}
		
		Line++;
		if(Col<8)
			Col=120+Col,Line-=2;
		else
			Col-=8;
		
		for (i = 0; i < 8; i++)
		{
			OLED_SetData(OLED_F8x16[Char - ' '][i + 8]);				//显示下半部分内容
		}
		Line--;
	}
}

void OLED_ShowString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(String[i]);
	}
}

void OLED_ShowSignedNum(int32_t Number, uint8_t Length)
{
	uint8_t i,j=0;
	uint32_t Number1;

	if (Number < 0)
	{
		OLED_ShowChar('-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++,j++)							
	{
		OLED_ShowChar(Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

void OLED_ShowFloat(double real,uint8_t NN,uint8_t N)
{
   unsigned char   i_Count=1;
   unsigned char   n[12]={0};
   long   j=1;  
   int    real_int=0;
   double decimal=0;
   unsigned int   real_decimal=0;
   if(real<0)
	 {
		 real_int=(int)(-real);
		 decimal=-real_int-real;
	 }
	 else
	 {
		 real_int=(int)real;
		 decimal=real-real_int;
   }
	 
   real_decimal=decimal*1e4;
   while(real_int/10/j!=0)
   {
      j=j*10;i_Count++;  
   } 
   n[0]=(real_int/10000)%10; 
   n[1]=(real_int/1000)%10;
   n[2]=(real_int/100)%10;
   n[3]=(real_int/10)%10;
   n[4]=(real_int/1)%10; 
   n[5]='.';
   n[6]=(real_decimal/1000)%10;
   n[7]=(real_decimal/100)%10;
   n[8]=(real_decimal/10)%10;
   n[9]=real_decimal%10;
   n[6+N]='\0'; 
   for(j=0;j<10;j++) n[j]=n[j]+16+32;
	 if(real<0) 
	 {		 
		 i_Count+=1;
		 n[5-i_Count]='-';
	 }
   n[5]='.';
   n[6+N]='\0';   
   OLED_ShowString((char *)&n[5-i_Count]); 
	 for(j=0;j<NN-i_Count;j++)
	 {
		OLED_ShowChar(' ');
	 }
}

void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
		
	OLED_ClearAll();				//OLED清屏
}



/*void OLED_ShowCN(uint8_t Line, uint8_t Column, char *String)
{
	int i = 0, j, len = strlen("中");
  while ((*String) != '\0')
  {
      char temp[4];
      for (j = 0; j < len; j++, String++)
      {
          temp[j] = *String;
      }
      temp[j] = '\0';
      for (j = 0; j < CN_Len; j++)
      {
          if (strcmp(temp, Chinese_Num[j]) == 0)
          {
              OLED_DrawPicture( Line , Column , 16 , 16 , Chinese_Str16[j]);
              break;
          }
      }
	 }
}*/
