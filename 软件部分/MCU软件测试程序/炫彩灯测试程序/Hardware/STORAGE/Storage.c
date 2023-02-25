#include "Storage.h"

uint8_t	TypeNum=0;	
uint8_t	TypeNumHex=0x00;			//0b0000 0000
uint8_t	PictNum=0;	
uint16_t	PictNumHex=0x0000;	//0b0000 0000 0000 0000

void Storage_Init()
{
	GetData();
}

void StorageData()
{
	
}

void GetData()
{
	
}

uint8_t StorageType(uint8_t Type)
{
	uint8_t i;			//0b0000 0000
	uint16_t j;
	for(j=0,i=0;j<236*4;j++,i++)
	{
		if(j>=(Type-1)*236&&j<=Type*236)W25QXX_WrBuff[j]=Color_Data[(j-(Type-1)*236)/59][i];
		else W25QXX_WrBuff[j]=0;
		if(i>=3)i=0;
	}
	W25QXX_Write_Sector(W25QXX_WrBuff,1,4096,0);
	i=0x01;
	i<<=(Type-1);
	i|=TypeNumHex;
	if(i==TypeNumHex)	return 0;
	else TypeNumHex=i;
	StorageData();
	return 1;
}

uint8_t GetType(uint8_t Type)
{
	uint8_t i;			//0b0000 0000
	uint16_t j;
	i=0x01;
	i<<=(Type-1);
	i|=TypeNumHex;
	if(i!=TypeNumHex)	return 0;
	W25QXX_Read_Sector(W25QXX_RdBuff,1,4096);
	for(j=(Type-1)*236,i=0;j<236*Type;j++,i++)
	{
		Color_Data[(j-(Type-1)*236)/59][i]=W25QXX_WrBuff[j];
		if(i>=3)i=0;
	}
	return 1;
}
