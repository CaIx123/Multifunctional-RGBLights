#ifndef __KEY_H
#define __KEY_H

#define KEY1   PBin(4) 
#define KEY2   PBin(5) 
#define LED    PCout(13) 		//1ÎªÃð

#include "sys.h"

extern uint8_t Sure_Flag;
extern uint8_t Back_Flag;

void KEY_Init(void);

#endif
