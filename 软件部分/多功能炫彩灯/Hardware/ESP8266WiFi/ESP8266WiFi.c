#include "ESP8266WiFi.h"

uint8_t DATABUFF[2][3840]={0},data=0,Buff_count0=0;
uint16_t Buff_count=0,LineCount=0,Str_count=0;
uint8_t Buff_CountFlag=0,show_flag=0,Str_countFlag=0;
uint8_t LastMode=0;
uint8_t count_n=0,returnflag=0;
uint8_t WiFiName[10]="None",IPAddress[16]="None";

void USART2_IRQHandler(void)                	//????1?§Ø???????
	{
	
  if(USART_GetITStatus(USART2,USART_IT_RXNE)!=0)  // ?????§Ø???¦Ë????
  {
    data=USART_ReceiveData(USART2);     // ?????????????
		
		if(Buff_CountFlag)
		{
			DATABUFF[Buff_count0][Buff_count]=data;
			Buff_count++;
			if(Buff_count>=3840)
			{
				Buff_count=0,Buff_count0=!Buff_count0;
				show_flag=1;
				LineCount++;
				if(LineCount>=30)	Buff_count=0,LineCount=0,Buff_CountFlag=0;
			}
		}
		if(Str_countFlag)
		{
			if(data==0xA5||(Str_count>=9&&Str_countFlag==1)||(Str_count>=15&&Str_countFlag==2))
			{
				switch(Str_countFlag)
				{
					case 1:
						WiFiName[Str_count]='\0';
						break;
					case 2:
						IPAddress[Str_count]='\0';
						MenuUpdateFlag[0]=1,MenuUpdateFlag[1]=1;
						break;
				}
				Str_countFlag=0;
				Str_count=0;
			}
			else
			{
				switch(Str_countFlag)
				{
					case 1:
						WiFiName[Str_count]=data;
						break;
					case 2:
						IPAddress[Str_count]=data;
						break;
				}
				Str_count++;
			}
		}
		
		if(data==0x5A&&!Buff_CountFlag&&!returnflag&&!Str_countFlag)	Buff_CountFlag=1,LastMode=(MenuMode==3?LastMode:MenuMode),MenuMode=3;
		if(!Buff_CountFlag&&!Str_countFlag)
		{
			switch(data)
			{
				case 'N':
					Str_countFlag=1;
					break;
				case 'I':
					Str_countFlag=2;
					break;
			}
		}
		
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
} 
	

void PicShow_Stroge()
{
	Uuup_Flag=0,Down_Flag=0;
	if(Back_Flag||Sure_Flag)	
	{
		if(Sure_Flag)
		{
			PictNum++,PictStorageNum++;
			if(PictStorageNum>9) PictStorageNum=1;
			if(PictNum>9) PictNum=9;
			StorageData(2);
		}
		Back_Flag=0,Sure_Flag=0;
		if(returnflag)
		{
			returnflag=0;
			MenuMode=LastMode,MenuUpdateFlag[0]=1,MenuUpdateFlag[1]=1,MenuUpdateFlag[2]=2;
			Buff_count=0,LineCount=0,Buff_CountFlag=0;
		}
	}
	if(show_flag)
	{
		StoragePicture(PictStorageNum+1,count_n,DATABUFF[!Buff_count0]);
		LCD_Showimage(0,0+8*count_n,240,8,DATABUFF[!Buff_count0]);
		show_flag=0;
		LED=!LED;
		count_n++;
		if(count_n>=30)
		{
			returnflag=1;
			count_n=0;
		}
	}
}
