#include "w25qxx.h" 
#include "spi.h"
#include "delay.h"
/***********************
说明：
W25Q64实际读写所用函数
引脚使用：
片选引脚CS 
GPIOPINB	GPIO_Pin_12
***********************/

/*********************************************
//页			Page												256B
//扇区		Sector	16页								4KB	4096B
//块			Block		16扇区							64KB
//W25Q64					128块,2048扇区			8MB
**********************************************/

void W25QXX_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
 
  W25QXX_CS=1;				//SPI FLASH不选中
	SPI2_Init();		   	//初始化SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式
}


//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR								默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0		FLASH区域写保护设置
//WEL								写使能锁定
//BUSY							忙标记位(1,忙;0,空闲)
//默认:0x00

/*读取W25QXX的状态寄存器*/
u8 W25QXX_ReadSR(void)   
{  
	u8 byte=0;   
	W25QXX_CS=0;                            //使能器件   
	SPI2_ReadWriteByte(W25X_ReadStatusReg); //发送读取状态寄存器命令    
	byte=SPI2_ReadWriteByte(0Xff);          //读取一个字节  
	W25QXX_CS=1;                            //取消片选     
	return byte;   
} 

/*写W25QXX状态寄存器*/
//只有SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)可以写!!!
void W25QXX_Write_SR(u8 sr)   
{   
	W25QXX_CS=0;                            //使能器件   
	SPI2_ReadWriteByte(W25X_WriteStatusReg);//发送写取状态寄存器命令    
	SPI2_ReadWriteByte(sr);               	//写入一个字节  
	W25QXX_CS=1;                            //取消片选     	      
}   

//W25QXX写使能	
//将WEL置位   
void W25QXX_Write_Enable(void)   
{
	W25QXX_CS=0;                          	//使能器件   
    SPI2_ReadWriteByte(W25X_WriteEnable); 	//发送写使能  
	W25QXX_CS=1;                           	//取消片选     	      
} 
//W25QXX写禁止	
//将WEL清零  

void W25QXX_Write_Disable(void)   
{  
	W25QXX_CS=0;                            //使能器件   
    SPI2_ReadWriteByte(W25X_WriteDisable);  //发送写禁止指令    
	W25QXX_CS=1;                            //取消片选     	      
} 		

//读取SPI FLASH  
//在指定地址开始读取指定长度的数据
//pBuffer:				数据存储区
//ReadAddr:				开始读取的地址(24bit	0x000000~0x7FFFFF)
//NumByteToRead:	要读取的字节数(最大65535,Flash共8388608字节)
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
		u16 i;   										    
		W25QXX_CS=0;                            	//使能器件   
    SPI2_ReadWriteByte(W25X_ReadData);         	//发送读取命令   
    SPI2_ReadWriteByte((u8)((ReadAddr)>>16));  	//发送24bit地址    
    SPI2_ReadWriteByte((u8)((ReadAddr)>>8));   
    SPI2_ReadWriteByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
		{ 
        pBuffer[i]=SPI2_ReadWriteByte(0XFF);   	//循环读数  
    }
		W25QXX_CS=1;  				    	      
}  

//从一页(0~32767)开始读出少于256个字节的数据
//pBuffer:				数据存储区长度1~256
//PageNum:				页码1~32768
//NumByteToWrite:	1~256
void W25QXX_Read_Page(u8* pBuffer,u16 PageNum,u16 NumByteToRead)
{
	u32 WRAddr=(PageNum-1)*256;
	W25QXX_Read(pBuffer,WRAddr,NumByteToRead);	
}

void W25QXX_Read_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToRead)
{ 
	u32 WRAddr=(SectorNum-1)*4096;
	W25QXX_Read(pBuffer,WRAddr,NumByteToRead);
}


//从一空页(1~32768)开始写入少于256个字节的数据
//pBuffer:				数据存储区长度1~256
//PageNum:				页码1~32768
//NumByteToWrite:	1~256
void W25QXX_Write_Page(u8* pBuffer,u16 PageNum,u16 NumByteToWrite)
{
		u16 i;  
		u32 WriteAddr=(PageNum-1)*256;
    W25QXX_Write_Enable();                  	//SET WEL 
		W25QXX_CS=0;                            	//使能器件   
    SPI2_ReadWriteByte(W25X_PageProgram);      	//发送写页命令   
    SPI2_ReadWriteByte((u8)((WriteAddr)>>16)); 	//发送24bit地址    
    SPI2_ReadWriteByte((u8)((WriteAddr)>>8));   
    SPI2_ReadWriteByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)SPI2_ReadWriteByte(pBuffer[i]);//循环写数  
		W25QXX_CS=1;                            	//取消片选 
		W25QXX_Wait_Busy();					   		//等待写入结束
} 

/*最常用*/
//从一扇区(1~2048)开始写入少于2048个字节的数据
//pBuffer:				数据存储区长度1~4096
//SectorNum:				页码1~2048
//NumByteToWrite:	1~4096
//Mode：					1为覆盖，0为不覆盖	覆盖指数据完全替换，不覆盖指指替换有数据的那部分
uint8_t W25QXX_RdBuff[4096];				//读取缓存
uint8_t W25QXX_WrBuff[4096];				//写入缓存
void W25QXX_Write_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToWrite,u8 Mode)
{
	u16 i,j;  
	u32 WRAddr=(SectorNum-1)*4096;
	u16 PageNum=(SectorNum-1)*16+1;
	//读取
	W25QXX_Read(W25QXX_RdBuff,WRAddr,4096);
	//擦除
	W25QXX_Erase_Sector(WRAddr);
	//缓存区替换计算
	for(i=0;i<4096;i++)
	{
		if(Mode)
		{
			if(i<NumByteToWrite)	W25QXX_WrBuff[i]=pBuffer[i];
			else	W25QXX_WrBuff[i]=W25QXX_RdBuff[i];
		}
		else
		{
			if(i<NumByteToWrite&&pBuffer[i])	W25QXX_WrBuff[i]=pBuffer[i];
			else	W25QXX_WrBuff[i]=W25QXX_RdBuff[i];
		}
	}
	//再写
	for(j=0;j<16;j++)
	{
//		W25QXX_Write_Enable();                  	//SET WEL 
//		W25QXX_CS=0;                            	//使能器件
//		SPI2_ReadWriteByte(W25X_PageProgram);      	//发送写页命令   
//		SPI2_ReadWriteByte((u8)((WRAddr)>>16)); 	//发送24bit地址    
//		SPI2_ReadWriteByte((u8)((WRAddr)>>8));   
//		SPI2_ReadWriteByte((u8)WRAddr);   
//		for(i=0;i<256;i++)SPI2_ReadWriteByte(W25QXX_WrBuff[i+j*256]);//循环写数  
//		W25QXX_CS=1;                            	//取消片选 
//		W25QXX_Wait_Busy();					   		//等待写入结束
//		
		W25QXX_Write_Page(&W25QXX_WrBuff[256*j],PageNum,256);
		PageNum+=1;
	}
} 


//擦除整个芯片		  
//等待时间超长...
void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();                 	 	//SET WEL 
    W25QXX_Wait_Busy();   
  	W25QXX_CS=0;                            	//使能器件   
    SPI2_ReadWriteByte(W25X_ChipErase);        	//发送片擦除命令  
		W25QXX_CS=1;                            	//取消片选     	      
		W25QXX_Wait_Busy();   				   		//等待芯片擦除结束
}   
//擦除一个扇区
//Dst_Addr:扇区地址 根据实际容量设置
//擦除一个山区的最少时间:150ms
void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
	W25QXX_Write_Enable();                  	//SET WEL 	 
	W25QXX_Wait_Busy();   
	W25QXX_CS=0;                            	//使能器件   
	SPI2_ReadWriteByte(W25X_SectorErase);      	//发送扇区擦除指令 
	SPI2_ReadWriteByte((u8)((Dst_Addr)>>16));  	//发送24bit地址    
	SPI2_ReadWriteByte((u8)((Dst_Addr)>>8));   
	SPI2_ReadWriteByte((u8)Dst_Addr);  
	W25QXX_CS=1;                            	//取消片选     	      
	W25QXX_Wait_Busy();   				   		//等待擦除完成
}  
//等待空闲
void W25QXX_Wait_Busy(void)   
{   
	while((W25QXX_ReadSR()&0x01)==0x01);  		// 等待BUSY位清空
}  
//进入掉电模式
void W25QXX_PowerDown(void)   
{ 
  	W25QXX_CS=0;                           	 	//使能器件   
    SPI2_ReadWriteByte(W25X_PowerDown);        //发送掉电命令  
	W25QXX_CS=1;                            	//取消片选     	      
    delay_us(3);                               //等待TPD  
}   
//唤醒
void W25QXX_WAKEUP(void)   
{  
  	W25QXX_CS=0;                            	//使能器件   
    SPI2_ReadWriteByte(W25X_ReleasePowerDown);	//  send W25X_PowerDown command 0xAB    
	W25QXX_CS=1;                            	//取消片选     	      
    delay_us(3);                            	//等待TRES1
}   


/*扇区写保护和状态寄存器写保护*/
void W25QXX_Write_Protect();				//扇区写保护
void W25QXX_SR_Protect();						//状态寄存器写保护
