#include "Storage.h"

uint8_t	TypeNum=0;	
uint8_t	TypeNumHex=0x00;			//无顺序0b0000 0000
uint8_t	PictNum=0;	
uint16_t	PictNumHex;	//有顺序

void Storage_Init()
{
//	StorageData(1);
//	StorageData(2);
//	StorageData(3);
//	StorageData(4);
	GetData();
}

//存储信息: 1.灯样式数量信息 2.灯样式存储位置信息 3.图片存储数量信息 4.字体颜色信息2 5.框架颜色信息 6.背景颜色信息
uint8_t StorgeData[9]={0};
void StorageData(uint8_t Num)
{
	uint8_t i;
	switch(Num)
	{
		case 1:
			StorgeData[0]=TypeNum;
			W25QXX_Write_Sector2(StorgeData,2,9,0,0);
			break;
		case 2:
			StorgeData[1]=TypeNumHex;
			W25QXX_Write_Sector2(StorgeData,2,9,1,1);
			break;
		case 3:
			StorgeData[2]=PictNum;
			W25QXX_Write_Sector2(StorgeData,2,9,2,2);
			break;
		case 4:
				StorgeData[3]=BackGronudColor&0x00FF;
				StorgeData[4]=BackGronudColor>>8;
				StorgeData[5]=RectColor&0x00FF;
				StorgeData[6]=RectColor>>8;
				StorgeData[7]=StrColor&0x00FF;
				StorgeData[8]=StrColor>>8;
				W25QXX_Write_Sector2(StorgeData,2,9,3,8);
			break;
	}
	for(i=0;i<9;i++)	StorgeData[i]=0;
	
}

void GetData()
{
	uint8_t i;
	W25QXX_Read_Sector(StorgeData,2,9);
	TypeNum=StorgeData[0];
	TypeNumHex=StorgeData[1];
	PictNum=StorgeData[2];
	BackGronudColor=StorgeData[3]|(StorgeData[4]<<8);
	RectColor=StorgeData[5]|(StorgeData[6]<<8);
	StrColor=StorgeData[7]|(StorgeData[8]<<8);
	for(i=0;i<9;i++)	StorgeData[i]=0;
}

//一张图4800*24 即48个扇区
//第3+n*48
void StoragePicture(uint8_t PicNum,uint8_t CountNum,uint8_t* PicArr)
{
	W25QXX_Write_Sector(PicArr,3+(PicNum-1)*48+CountNum,4096,0);
	W25QXX_Write_Sector(&(PicArr[4096]),4+(PicNum-1)*48+CountNum,4800-4096,0);
}

//Mode: 1.只获取图片作为壁纸	2.显示图片
uint8_t GetShowPicture(uint8_t PicNum,uint8_t Mode)
{
	if(PicNum>PictNum) return 0;
	if(Mode==1){}
	else if(Mode==2){}
		
	return 1;
}

uint8_t TypeWriteBuff[177*4];		//59
uint8_t StorageType(uint8_t Type)
{
	uint8_t i;			//0b0000 0000
	uint16_t j;
	for(j=0,i=0;j<177*4;j++,i++)
	{
		if(j>=(Type-1)*177&&j<=Type*177)TypeWriteBuff[j]=Color_Data[(j-(Type-1)*177)/59][i];
		else TypeWriteBuff[j]=0;
		if(i>=3)i=0;
	}
	W25QXX_Write_Sector2(TypeWriteBuff,1,177*4,(Type-1)*177,Type*177);
	i=0x01;
	i<<=(Type-1);
	i|=TypeNumHex;
	if(i==TypeNumHex)	return 0;
	else TypeNumHex=i,TypeNum++;
	StorageData(1);
	StorageData(2);
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
	W25QXX_Read_Sector(TypeWriteBuff,1,177*4);
	for(j=(Type-1)*177,i=0;j<177*Type;j++,i++)
	{
		Color_Data[(j-(Type-1)*177)/59][i]=TypeWriteBuff[j];
		if(i>=3)i=0;
	}
	return 1;
}
