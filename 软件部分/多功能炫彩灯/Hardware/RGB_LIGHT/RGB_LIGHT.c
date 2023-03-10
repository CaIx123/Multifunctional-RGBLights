#include "RGB_LIGHT.h"
#include "RGB_ColorNUMs.h" 


uint8_t ON_Data[N_Max]={0};
uint8_t Color_Data[N_Max][3]={0};
uint8_t RGB_BeginNum=0,RGB_EndNum=0;

uint32_t	RGBColors[10][2]={
	{Red,RED},{Orange,ORANGE},{Yellow,YELLOW},{Green,GREEN},{Meaq,MEAQ},
	{Blue,BLUE},{Pink,PINK},{Cyan,CYAN},{Gold,GOLD},{RosyBrown,ROSYBROWN}};

void DATA_Pin_Init(void)
{    	 
	uint8_t i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = DATA_PINA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOA,DATA_PINA );
	PINOUT=0;
//	for(i=0;i<58;i++)
//	{
//		RGB_SETBE(i+1,i+1);
//		if(i%3==0)	Set_RGBDATA(Red);
//		else if(i%3==1) Set_RGBDATA(Green);
//		else if(i%3==2) Set_RGBDATA(Blue);
//	}
}

void RGB_Send_1Code(void)
{
	uint16_t i=0;
	PINOUT=1;
	for(i=0;i<4;i++);
	PINOUT=0;
	for(i=0;i<4;i++);
}

void RGB_Send_0Code(void)
{
	uint16_t i=0;
	PINOUT=1;
	for(i=0;i<1;i++);
	PINOUT=0;
	for(i=0;i<4;i++);
}

void RGB_Reset(void)
{
	delay_us(300);
}

void RGB_Send_1Bits(uint8_t Data)
{
	if(Data)	RGB_Send_1Code();
	else			RGB_Send_0Code();
}

/**************
默认为BRG值发送
**************/
void RGB_Send_24Bits(uint32_t Data)				//0xFF(FFFFFF)	
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		RGB_Send_1Bits((uint8_t)(Data&0x00000001));
		Data>>=1;
	}
}

/****************
按照RGB总体值发送
****************/
void Send_RGBDATA(uint32_t Data)			//FF1122		改为22FF11
{
	uint8_t i;				
	uint32_t data=0x00000000;
	data|=Data<<16;					//220000
	data|=Data>>8;				//22FF11
	for(i=0;i<24;i++)
	{
		RGB_Send_1Bits((uint8_t)(data&0x00000001));
		data>>=1;
	}
}
/****************
按照RGB各个值发送
****************/
void Send_RGB(uint8_t R,uint8_t G,uint8_t B)
{
	uint32_t Data=0x00000000;
	Data|=((uint32_t)B<<16);
	Data|=((uint32_t)R<<8);
	Data|=((uint32_t)G);
	RGB_Send_24Bits(Data);
}

void RGB_SETBE(uint8_t BeginNum,uint8_t EndNum)
{
	RGB_BeginNum=BeginNum;
	RGB_EndNum=EndNum;
}

uint8_t Set_RGBDATA(uint32_t Data)
{
	uint8_t Num;
	if(!RGB_EndNum||!RGB_BeginNum)return 0;
	if(RGB_EndNum<RGB_BeginNum)
		Num=RGB_BeginNum,RGB_BeginNum=RGB_EndNum,RGB_EndNum=Num;
	for(Num=RGB_BeginNum;Num<=RGB_EndNum;Num++)
	{
		Color_Data[Num-1][0]=Data>>16;
		Color_Data[Num-1][1]=(Data>>8)&0x000000FF;
		Color_Data[Num-1][2]=Data&0x000000FF;
	}
}

uint8_t Set_RGB(uint8_t R,uint8_t G,uint8_t B)		//以RGB值设置
{
	uint8_t Num;
	if(!RGB_EndNum||!RGB_BeginNum)return 0;
	if(RGB_EndNum<RGB_BeginNum)
		Num=RGB_BeginNum,RGB_BeginNum=RGB_EndNum,RGB_EndNum=Num;
	for(Num=RGB_BeginNum;Num<=RGB_EndNum;Num++)
	{
		Color_Data[Num-1][0]=R;
		Color_Data[Num-1][1]=G;
		Color_Data[Num-1][2]=B;
	}
	return 1;
}

void RGB_Refresh_All()																					//更新整个灯带
{
	uint8_t i;
	for(i=0;i<N_Max;i++)
	{
		Send_RGB(Color_Data[i][0],Color_Data[i][1],Color_Data[i][2]);
	}
}

void RGB_Off()
{
	uint8_t i;
	for(i=0;i<N_Max;i++)
	{
		Send_RGB(0,0,0);
	}
}

uint8_t Flow_Interval=10,FlowingFlag=0,FlowingType=1;
void SetFlowingType(uint8_t FlowingTypeNum)
{
	FlowingType=FlowingTypeNum;
}

void SetInterval(uint8_t interval)
{
	Flow_Interval=interval;
}

//uint8_t Color_Data[N_Max][3]={0};
uint8_t intervalCount=0;
void Flowing()
{
	uint8_t Temp[3];
	short int i,j;
	if(!FlowingFlag)	return;
	
	intervalCount++;
	if(intervalCount>=Flow_Interval)	
	{
		intervalCount=0;
		if(FlowingFlag)
		{
			switch(FlowingType)
			{
				case 1:
					for(i=0;i<3;i++)
					{
						Temp[i]=Color_Data[N_Max-1][i];
					}
					for(j=N_Max-2;j>=0;j--)
					{
						for(i=0;i<3;i++)
						{
							Color_Data[j+1][i]=Color_Data[j][i];
						}
					}
					for(i=0;i<3;i++)
					{
						Color_Data[0][i]=Temp[i];
					}
					break;
				case 2: 
					for(i=0;i<3;i++)
					{
						Temp[i]=Color_Data[0][i];
					}
					for(j=0;j<=N_Max-2;j++)
					{
						for(i=0;i<3;i++)
						{
							Color_Data[j][i]=Color_Data[j+1][i];
						}
					}
					for(i=0;i<3;i++)
					{
						Color_Data[N_Max-1][i]=Temp[i];
					}
					break;
				case 3:
					for(i=0;i<3;i++)
					{
						Temp[i]=Color_Data[N_Max/2-1][i];
					}
					for(j=N_Max/2-2;j>=0;j--)
					{
						for(i=0;i<3;i++)
						{
							Color_Data[j+1][i]=Color_Data[j][i];
						}
					}
					for(i=0;i<3;i++)
					{
						Color_Data[0][i]=Temp[i];
					}
					
					for(i=0;i<3;i++)
					{
						Temp[i]=Color_Data[N_Max/2][i];
					}
					for(j=N_Max/2;j<=N_Max-2;j++)
					{
						for(i=0;i<3;i++)
						{
							Color_Data[j][i]=Color_Data[j+1][i];
						}
					}
					for(i=0;i<3;i++)
					{
						Color_Data[N_Max-1][i]=Temp[i];
					}
					break;
				case 4:		//29
					for(j=0;j<N_Max/2;j++)
					{
						for(i=0;i<3;i++)
						{
							Temp[i]=Color_Data[j*2][i];
							Color_Data[j*2][i]=Color_Data[j*2+1][i];
							Color_Data[j*2+1][i]=Temp[i];
						}
					}
					break;
			}
		}
		else return;
		RGB_Refresh_All();
	}
}
