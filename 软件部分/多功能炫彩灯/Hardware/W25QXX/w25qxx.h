#ifndef __FLASH_H
#define __FLASH_H			    
#include "sys.h" 

#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17

extern uint8_t W25QXX_RdBuff[4096];
extern uint8_t W25QXX_WrBuff[4096];

#define	W25QXX_CS 		PBout(12)  		//W25QXX的片选信号
				 
////////////////////////////////////////////////////////////////////////////
 
//指令表
#define W25X_WriteEnable		0x06 			//写使能
#define W25X_WriteDisable		0x04 			//写禁能
#define W25X_ReadStatusReg		0x05 		//读状态寄存器
#define W25X_WriteStatusReg		0x01 		//写状态寄存器
#define W25X_ReadData			0x03 				//读数据
#define W25X_FastReadData		0x0B 			//快读
#define W25X_FastReadDual		0x3B 			//快读双输出
#define W25X_PageProgram		0x02 			//页编程
#define W25X_BlockErase			0xD8 			//块擦除
#define W25X_SectorErase		0x20 			//扇区擦除
#define W25X_ChipErase			0xC7 			//芯片擦除
#define W25X_PowerDown			0xB9 			//掉电
#define W25X_ReleasePowerDown	0xAB 		
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

void W25QXX_Init(void);
u16  W25QXX_ReadID(void);  	    		//读取FLASH ID
u8	 W25QXX_ReadSR(void);        		//读取状态寄存器 
void W25QXX_Write_SR(u8 sr);  			//写状态寄存器
void W25QXX_Write_Enable(void);  		//写使能 
void W25QXX_Write_Disable(void);		//写保护

/*读写函数*/
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //读取flash
void W25QXX_Read_Page(u8* pBuffer,u16 PageNum,u16 NumByteToRead);   
void W25QXX_Read_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToRead);   
void W25QXX_Write_Page(u8* pBuffer,u16 PageNum,u16 NumByteToWrite);
void W25QXX_Write_Sector(u8* pBuffer,u16 SectorNum,u16 NumByteToWrite,u8 Mode);
void W25QXX_Write_Sector2(u8* pBuffer,u16 SectorNum,u16 NumByteToWrite,u16 S,u16 E);
/*擦除函数*/
void W25QXX_Erase_Chip(void);    	  	//整片擦除
void W25QXX_Erase_Sector(u32 Dst_Addr);	//扇区擦除

/*扇区写保护和状态寄存器写保护*/	//懒得开发
void W25QXX_Write_Protect();				//扇区写保护
void W25QXX_SR_Protect();						//状态寄存器写保护


void W25QXX_Wait_Busy(void);           //等待空闲
void W25QXX_PowerDown(void);        	//进入掉电模式
void W25QXX_WAKEUP(void);							//唤醒
#endif
















