#include "Storage.h"

uint8_t	TypeNum=0;	
uint8_t	TypeNumHex=0x00;			//无顺序存储样式0b0000 0000
uint8_t	PictNum=0;	
uint8_t	PictStorageNum=0;			//顺序存储图片
uint8_t BackNum=0;						//背景图片信息
uint8_t StorgeData[11]={0};

void Storage_Init()
{
//	StorageData(1);
//	StorageData(2);
//	StorageData(3);
//	StorageData(4);

	GetData();
}

//存储信息: 1.灯样式数量信息(0) 灯样式存储位置信息(1)
//					2.图片存储数量信息(2) 图片存储位置信息(3) 
//					3.图片背景位置信息(4)
//					4.字体颜色信息(5,6)  框架颜色信息(7,8)  背景颜色信息(9,10) 

void StorageData(uint8_t Num)
{
	uint8_t i;
	switch(Num)
	{
		case 1:
			StorgeData[0]=TypeNum;
			StorgeData[1]=TypeNumHex;
			W25QXX_Write_Sector2(StorgeData,2,11,0,1);
			break;
		case 2:
			StorgeData[2]=PictNum;
			StorgeData[3]=PictStorageNum;
			W25QXX_Write_Sector2(StorgeData,2,11,2,3);
			break;
		case 3:
			StorgeData[4]=BackNum;
			W25QXX_Write_Sector2(StorgeData,2,11,4,4);
			break;
		case 4:
			StorgeData[5]=BackGronudColor&0x00FF;
			StorgeData[6]=BackGronudColor>>8;
			StorgeData[7]=RectColor&0x00FF;
			StorgeData[8]=RectColor>>8;
			StorgeData[9]=StrColor&0x00FF;
			StorgeData[10]=StrColor>>8;
			W25QXX_Write_Sector2(StorgeData,2,11,5,10);
			break;
	}
	for(i=0;i<11;i++)	StorgeData[i]=0;
	
}

void GetData()
{
	uint8_t i;
	W25QXX_Read_Sector(StorgeData,2,11);
	TypeNum=StorgeData[0];
	TypeNumHex=StorgeData[1];
	
	PictNum=StorgeData[2];
	PictStorageNum=StorgeData[3];
	
	BackNum=StorgeData[4];
	BackGronudColor=StorgeData[5]|(StorgeData[6]<<8);
	RectColor=StorgeData[7]|(StorgeData[8]<<8);
	StrColor=StorgeData[9]|(StorgeData[10]<<8);

	for(i=0;i<11;i++)	StorgeData[i]=0;
}

//一张图3840*30 即30个扇区
//第3+n*30
void StoragePicture(uint8_t PicNum,uint8_t CountNum,uint8_t* PicArr)
{
	W25QXX_Write_Sector(PicArr,3+(PicNum-1)*30+CountNum,3840,1);
}

//Mode: 1.获取图片作为壁纸	2.显示图片
uint8_t GetShowPicture(uint8_t PicNum)
{
	uint8_t count_n;
	if(PicNum>PictNum) return 0;
	for(count_n=0;count_n<30;count_n++)
	{
		W25QXX_Read_Sector(DATABUFF[0],3+(PicNum-1)*30+count_n,3840);
		LCD_Showimage(0,0+8*count_n,240,8,&(DATABUFF[0][0]));
	}

	return 1;
}

uint8_t TypeWriteBuff[177*4];		//59
//0 1 2 3		1 1 2 3
uint8_t StorageType(uint8_t Type)
{
	uint8_t i;			//0b0000 0000
	uint16_t j;
	for(j=0,i=0;j<177*4;j++,i++)
	{
		if((j>=(Type-1)*177)&&(j<Type*177))TypeWriteBuff[j]=Color_Data[(j-(Type-1)*177)/3][i];
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
		Color_Data[(j-(Type-1)*177)/3][i]=TypeWriteBuff[j];
		if(i>=3)i=0;
	}
	return 1;
}
