#ifndef __STORAGE_H
#define __STORAGE_H			    
#include "sys.h" 

extern uint8_t	TypeNum;	
extern uint8_t	PictNum;	


void Storage_Init();
uint8_t StorageType(uint8_t Type);
uint8_t GetType(uint8_t Type);
void StoragePicture(uint8_t PicNum,uint8_t CountNum,uint8_t* PicArr);
void GetPicture();

void StorageData(uint8_t Num);
void GetData();

#endif
