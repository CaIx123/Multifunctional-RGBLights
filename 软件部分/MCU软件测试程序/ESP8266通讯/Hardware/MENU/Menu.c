#include "Menu.h"
#include "oled.h"
#include "string.h"

uint16_t BackGronudColor=WHITE;
uint16_t RectColor=LIGHTBLUE;
uint16_t StrColor=BLACK;

struct Pagedata MenuPage[5][5];
uint8_t	MenuMode=1;				//1.设置 2.天气时钟 3.图片显示
uint8_t BackNum=0;

void LCD_Menu_Init()
{
	/*第一级	1*/
	MenuPage[0][0].ChoiceNum=4;
	MenuPage[0][0].CurrentChoice=1;
	strcpy(MenuPage[0][0].Str[0],"LightSet ");
	strcpy(MenuPage[0][0].Str[1],"Flowing  ");
	strcpy(MenuPage[0][0].Str[2],"BackSet  ");
	strcpy(MenuPage[0][0].Str[3],"WeathClk ");
	/*第二级 	4*/
	MenuPage[1][0].ChoiceNum=4;
	MenuPage[1][0].CurrentChoice=1;
	strcpy(MenuPage[1][0].Str[0],"Individul");
	strcpy(MenuPage[1][0].Str[1],"Adjust   ");
	strcpy(MenuPage[1][0].Str[2],"TypeGet  ");
	strcpy(MenuPage[1][0].Str[3],"Save     ");

	
	MenuPage[2][0].ChoiceNum=4;
	MenuPage[2][0].CurrentChoice=1;
	strcpy(MenuPage[2][0].Str[0],"Type?    ");
	strcpy(MenuPage[2][0].Str[1],"Speed    ");
	strcpy(MenuPage[2][0].Str[2],"Run      ");
	strcpy(MenuPage[2][0].Str[3],"Stop     ");
	
	MenuPage[3][0].ChoiceNum=4;
	MenuPage[3][0].CurrentChoice=1;
	strcpy(MenuPage[3][0].Str[0],"BackGrond");
	strcpy(MenuPage[3][0].Str[1],"MenuColor");
	strcpy(MenuPage[3][0].Str[2],"SaveMenu ");
	strcpy(MenuPage[3][0].Str[3],"Picture  ");
//	strcpy(MenuPage[3][0].Str[1],"WordColor");
//	strcpy(MenuPage[3][0].Str[2],"FramColor");
//	strcpy(MenuPage[3][0].Str[3],"BackColor");
	
	MenuPage[4][0].ChoiceNum=3;
	MenuPage[4][0].CurrentChoice=1;
	strcpy(MenuPage[4][0].Str[0],"Update   ");
	strcpy(MenuPage[4][0].Str[1],"Switch   ");
	strcpy(MenuPage[4][0].Str[2],"Settime  ");
	/*第三级 	15*/
	MenuPage[1][1].ChoiceNum=3;
	MenuPage[1][1].CurrentChoice=1;
	strcpy(MenuPage[1][1].Str[0],"Num?To?  ");
	strcpy(MenuPage[1][1].Str[1],"R?G?B?   ");
	strcpy(MenuPage[1][1].Str[2],"Color?   ");
	MenuPage[1][2].ChoiceNum=3;
	MenuPage[1][2].CurrentChoice=1;
	strcpy(MenuPage[1][2].Str[0],"On       ");
	strcpy(MenuPage[1][2].Str[1],"Off      ");
	strcpy(MenuPage[1][2].Str[2],"ReSet    ");
	
	MenuPage[1][3].ChoiceNum=0;
	MenuPage[1][3].CurrentChoice=0;
	MenuPage[1][4].ChoiceNum=0;
	MenuPage[1][4].CurrentChoice=0;
	
	MenuPage[2][1].ChoiceNum=0;
	MenuPage[2][1].CurrentChoice=0;
	MenuPage[2][2].ChoiceNum=0;
	MenuPage[2][2].CurrentChoice=0;
	MenuPage[2][3].ChoiceNum=0;
	MenuPage[2][3].CurrentChoice=0;
	MenuPage[2][4].ChoiceNum=0;
	MenuPage[2][4].CurrentChoice=0;
	
	MenuPage[3][1].ChoiceNum=2;
	MenuPage[3][1].CurrentChoice=1;
	strcpy(MenuPage[3][1].Str[0],"Origin   ");
	strcpy(MenuPage[3][1].Str[1],"Saved    ");
	MenuPage[3][2].ChoiceNum=3;
	MenuPage[3][2].CurrentChoice=1;
	strcpy(MenuPage[3][2].Str[0],"WordColor");
	strcpy(MenuPage[3][2].Str[1],"FramColor");
	strcpy(MenuPage[3][2].Str[2],"BackColor");
	MenuPage[3][3].ChoiceNum=2;
	MenuPage[3][3].CurrentChoice=1;
	strcpy(MenuPage[3][3].Str[0],"SaveMenu ");
	strcpy(MenuPage[3][3].Str[1],"ResetMenu");
	
	MenuPage[3][4].ChoiceNum=0;
	MenuPage[3][4].CurrentChoice=0;
	
	MenuPage[4][1].ChoiceNum=0;
	MenuPage[4][1].CurrentChoice=0;
	MenuPage[4][2].ChoiceNum=0;
	MenuPage[4][2].CurrentChoice=0;
	MenuPage[4][3].ChoiceNum=0;
	MenuPage[4][3].CurrentChoice=0;
	/*显示轮廓*/
	LCD_ShowOutline();
	LCD_UpdatePage(0,0);
}

void LCD_ShowBackGround()
{
	if(BackNum==0)
	{
		LCD_Clear(BackGronudColor);
		LCD_SetColor(BackGronudColor,YELLOW);
		Draw_Circle(100,60,25);
		LCD_DrawPoint_big(100,60);
		LCD_SetColor(BackGronudColor,LGRAY);
		Draw_Circle(200,80,20);
		LCD_DrawPoint_big(200,80);
		LCD_SetColor(BackGronudColor,GREEN);
		Draw_Circle(120,200,30);
		LCD_DrawPoint_big(120,200);
		LCD_SetColor(BackGronudColor,RED);
		Draw_Circle(60,200,10);
		LCD_DrawPoint_big(60,200);
	}
	
}

/*用于天气时钟和设置界面显示*/
void LCD_ShowOutline()
{
	uint8_t i;
	if(MenuMode==3) return;
	/*背景*/
	LCD_ShowBackGround();
	/*画边框*/
	LCD_SetColor(BackGronudColor,RectColor);
	for(i=0;i<5;i++)
	{
		LCD_DrawRectangle(i,i,239-i,239-i);
		LCD_DrawLine(0,39-i,239,39-i);
		LCD_DrawLine(0,199+i,239,199+i);
	}
	/*显示字符*/
	LCD_SetColor(BackGronudColor,StrColor);
//	LCD_ShowString(160,12,"Mode:");
//	LCD_ShowNum(234,12,MenuMode,1);
//	LCD_ShowString(40,12,"Page:");
////	LCD_ShowNum(80,12,CurrentPage[0],1);
////	LCD_ShowNum(96,12,CurrentPage[1],1);
	switch(MenuMode)
	{
		case 1:
			LCD_Showhanzi(12+16*0,212,0,1);			//存
			LCD_Showhanzi(12+16*1,212,1,1);			//储
			LCD_Showhanzi(12+16*2,212,2,1);			//样
			LCD_Showhanzi(12+16*3,212,3,1);			//式
			LCD_ShowChar(12+16*4,212,':',0);
			LCD_ShowNum(12+16*5,212,TypeNum,1);
			LCD_Showhanzi(132+16*0,212,0,1);			//存
			LCD_Showhanzi(132+16*1,212,1,1);			//储
			LCD_Showhanzi(132+16*2,212,4,1);			//图
			LCD_Showhanzi(132+16*3,212,5,1);			//片
			LCD_ShowChar(132+16*4,212,':',0);
			LCD_ShowNum(132+16*5,212,PictNum,1);
			
			break;
		case 2:
			break;
	}
}


void LCD_UpdatePage(uint8_t CurrentPage0,uint8_t CurrentPage1)
{
	uint8_t i;
	uint16_t x=80,y=40;
//	LCD_ShowNum(80,12,CurrentPage[0],1);
//	LCD_ShowNum(96,12,CurrentPage[1],1);
//	LCD_ShowNum(112,12,MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum,5);
//	LCD_ShowNum(112+16,12,MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum,1);
	LCD_SetColor(BackGronudColor,GRAY);
	LCD_ShowString(8,12,"         ");
	LCD_ShowString(8,12,(const char*)WiFiName);
	LCD_ShowString(8+8*10,12,"Ip:");
	LCD_ShowString(8+8*13,12,"               ");
	LCD_ShowString(8+8*13,12,(const char*)IPAddress);
	LCD_SetColor(BackGronudColor,StrColor);
	LCD_ShowNum(12+16*5,212,TypeNum,1);
	LCD_ShowNum(132+16*5,212,PictNum,1);
	for(i=0;i<4;i++)
	{
		if(i>=MenuPage[CurrentPage0][CurrentPage1].ChoiceNum)
		{
			LCD_SetColor(BackGronudColor,StrColor);
			LCD_ShowString(x,y+12,"           ");
			y+=40;
			continue;
		}
		if(i==(MenuPage[CurrentPage0][CurrentPage1].CurrentChoice-1))
			LCD_SetColor(RectColor,StrColor);
		else
			LCD_SetColor(BackGronudColor,StrColor);
		LCD_ShowNum(x,y+12,i+1,1);
		LCD_ShowChar(x+8,y+12,':',0);
		LCD_ShowString(x+16,y+12,MenuPage[CurrentPage0][CurrentPage1].Str[i]);
		y+=40;
	}
	LCD_SetColor(BackGronudColor,StrColor);
}

uint8_t FunctionFlag=0;			//函数标志位
uint8_t FunctionStopFlag=0;
/*菜单更新函数*/
void LCD_UpdateMenu()
{
	if(!MenuUpdateFlag[0])return;		//无刷新
	if(FunctionFlag)
	{
		LCD_UpdatePage(4,1);		//清屏
		MenuUpdateFlag[0]=0;
		return;
	}
	if(MenuUpdateFlag[2])
	{
		LCD_ShowOutline();
		if(MenuUpdateFlag[2]!=2)MenuUpdateFlag[0]=0;
		MenuUpdateFlag[2]=0;
		return;
	}
	if(MenuUpdateFlag[1])
	{
		LCD_UpdatePage(CurrentPage[0],CurrentPage[1]);
		MenuUpdateFlag[0]=0;
		MenuUpdateFlag[1]=0;
		return;
	}

}

/*菜单切换函数*/

uint8_t MenuUpdateFlag[3]={0,0,0};	//刷新标示位	页刷新标示位	菜单刷新标示位	
uint8_t CurrentPage[2]={0,0};		//菜单级数


//							(1,1)
//				(1,0)	(1,2)
//							(1,3)
//	(0,0)	(2,0)	...
//				(3,0)	...
//

uint8_t ReturnShowNum=0;	//1为OK,2为BACK,3及以上为函数特有

void LCD_Switch()
{
	if(MenuMode==2)
	{
		if(Sure_Flag)MenuMode=1,Sure_Flag=0;
		MenuUpdateFlag[0]=1,MenuUpdateFlag[1]=1;
		return;
	}
	if(Back_Flag)
	{
		if(FunctionFlag)
		{
			FunctionStopFlag=1,Back_Flag=0,ReturnShowNum=2;
			return;
		}
		if(CurrentPage[1]) 
		{
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
			CurrentPage[1]=0;
		}
		else if(CurrentPage[0])
		{
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
			CurrentPage[0]=0;
		}
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Back_Flag=0;
	}
	if(FunctionFlag)return;
	if(Sure_Flag)
	{
		if(!CurrentPage[0]) CurrentPage[0]=MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice;
		else if(!CurrentPage[1]&&MenuPage[CurrentPage[0]][MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice].ChoiceNum!=0) CurrentPage[1]=MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice;
		else if(!FunctionFlag)MenuUpdateFlag[0]=1,FunctionFlag=1;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Sure_Flag=0;
	}
	if(Uuup_Flag)
	{
		if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice>1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice-=1;
		else if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice<=1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Uuup_Flag=0;
	}
	else if(Down_Flag)
	{
		if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice<MenuPage[CurrentPage[0]][CurrentPage[1]].ChoiceNum)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice+=1;
		else if(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice>=1)
			MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice=1;
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
		Down_Flag=0;
	}
}

uint8_t NumGet=1;
void Show_Function(uint8_t NO,uint8_t Count,uint8_t Count_Max)
{
	uint8_t i=1;
	if(NO==7)i=2;
	if(Uuup_Flag)NumGet+=i,Uuup_Flag=0;
	else if(Down_Flag)NumGet-=i,Down_Flag=0;
//	LCD_SetColor(BackGronudColor,RED);
//	LCD_ShowString(80,172,"FuncRunning");
//	LCD_SetColor(BackGronudColor,StrColor);
	switch(NO)
	{
		case 1:
			LCD_ShowString(80,52,"   Type?");
			LCD_ShowString(80,92,"  Num:1to4");
			if(NumGet>4)NumGet=1;
			if(NumGet==0)NumGet=4;
			break;
		case 2:
			LCD_ShowString(80,52," Picture?");
			LCD_ShowString(80,92,"  Num:1to9");
			if(NumGet>9)NumGet=1;
			if(NumGet==0)NumGet=9;
			break;
		case 3:
			LCD_ShowString(80,52,"  Color?");
			LCD_ShowString(80,92," Num:0to9");
			for(i=0;i<10;i++)
			{
				LCD_SetColor((uint16_t)RGBColors[i][1],BLACK);
				LCD_ShowNum(80+8*i,172,i,1);
			}
			LCD_SetColor(BackGronudColor,StrColor);
			if(NumGet==0xFF)NumGet=9;
			if(NumGet>9)NumGet=0;
			break;
		case 4:
			LCD_ShowString(80,52,"Times/100ms");
			LCD_ShowString(80,92," Num:1to10");
			if(NumGet>10)NumGet=1;
			if(NumGet==0)NumGet=10;
			break;
		case 5:
			LCD_ShowString(80,52," Minute?");
			LCD_ShowString(80,92," Num:1to10");
			if(NumGet>10)NumGet=1;
			if(NumGet==0)NumGet=10;
			break;
		case 6:
			LCD_ShowString(80,52,"  Num?to?");
			LCD_ShowString(80,92," Num:1to59");
			if(NumGet>59)NumGet=1;
			if(NumGet==0)NumGet=59;
			break;
		case 7:
			LCD_ShowString(80,52,"ColorR?G?B?");
			LCD_ShowString(80,92," Num:0to255");
			break;
	}
	switch(Count_Max)
	{
		case 1:
			LCD_ShowNum(80+8*4,132,NumGet,3);
			break;
		case 2:
			LCD_ShowNum(80+64*(Count-1),132,NumGet,3);	
			for(i=Count;i<Count_Max;i++)
				LCD_ShowNum(80+64*i,132,1,3);	
			break;
		case 3:
			LCD_ShowNum(80+32*(Count-1),132,NumGet,3);	
			for(i=Count;i<Count_Max;i++)
				LCD_ShowNum(80+32*i,132,0,3);	
			break;		
	}
				//112
}

void LCD_ReturnShow()
{
	LCD_UpdatePage(4,1);		//清屏
	 switch(ReturnShowNum)
	 {
		 case 0:
				break;
		 case 1:
				LCD_ShowString(120-8,80+12,"OK");
				ReturnShowNum=0;
				break;
		 case 2:
				LCD_ShowString(120-8*2,80+12,"BACK");
				ReturnShowNum=0;
				break;
		 case 3:
				LCD_ShowString(80,80+12,"Successful");
				ReturnShowNum=0;
				break;
		 case 4:
				LCD_ShowString(120-8*3,80+12,"Failed");
				ReturnShowNum=0;
				break;
		 case 5:
				LCD_ShowString(80,80+12,"NoFunction");
				ReturnShowNum=0;
				break;
		 case 6:
				LCD_ShowString(120-8*3,80+12,"Cover");
				ReturnShowNum=0;
				break;
	 }
	 delay_ms(200);
	 LCD_ShowString(80,80+12,"           ");
}

uint8_t	LCD_FUCBUFF[3];
void LCD_Function()
{
	static uint8_t Func_count=1;
	if(!FunctionFlag||MenuMode==2)return;
	switch(CurrentPage[0])
	{
		case 1:		//LightSet
			switch(CurrentPage[1])
			{
				case 0:
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 3:			//TypeGet
							Show_Function(1,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1;
								if(GetType(NumGet))ReturnShowNum=3,RGB_Refresh_All();
								else ReturnShowNum=4;
								NumGet=1;
							}
							break;
						case 4:			//Save
							Show_Function(1,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1;
								if(StorageType(NumGet))ReturnShowNum=3;
								else ReturnShowNum=6;
								NumGet=1;
							}
							break;
					}
					break;
				case 1:		//Individul
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 1:
							Show_Function(6,Func_count,2);
							if(Sure_Flag)
							{
								
								Sure_Flag=0,LCD_FUCBUFF[Func_count-1]=NumGet;
								NumGet=1;;
								Func_count++;
								if(Func_count>2) 
								{
									FunctionStopFlag=1,Func_count=1;
									RGB_SETBE(LCD_FUCBUFF[0],LCD_FUCBUFF[1]);
									ReturnShowNum=3;
								}
							}
							break;
						case 2:
							Show_Function(7,Func_count,3);
							if(Sure_Flag)
							{
								
								Sure_Flag=0,LCD_FUCBUFF[Func_count-1]=NumGet;
								NumGet=0;
								Func_count++;
								if(Func_count>3) 
								{
									if(Set_RGB(LCD_FUCBUFF[0],LCD_FUCBUFF[1],LCD_FUCBUFF[2]))RGB_Refresh_All(),ReturnShowNum=3;	
									else ReturnShowNum=4;
									FunctionStopFlag=1,Func_count=1;
								}
								
							}
							break;
						case 3:
							Show_Function(3,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1;	
								if(Set_RGBDATA(RGBColors[NumGet][0]))RGB_Refresh_All(),ReturnShowNum=3;	
								else ReturnShowNum=4;
							}
							break;
					}
					break;
				case 2:			//Adjust
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 1:
							FunctionStopFlag=1,ReturnShowNum=1;
							RGB_Refresh_All();
							break;
						case 2:
							FunctionStopFlag=1,ReturnShowNum=1;
							RGB_Off();
							break;
						case 3:
							FunctionStopFlag=1,ReturnShowNum=1;
							RGB_SETBE(1,59);
							Set_RGB(0,0,0);
							RGB_Refresh_All();
							break;
					}
					break;

			}
			break;
		case 2:		//Flowing
			switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
			{
				case 1:		//Type?
					Show_Function(1,1,1);
					if(Sure_Flag)
					{
						Sure_Flag=0,FunctionStopFlag=1;
						SetFlowingType(NumGet);
						NumGet=1,ReturnShowNum=1;
					}
					break;
				case 2:		//Speed
					Show_Function(4,1,1);
					if(Sure_Flag)
					{
						Sure_Flag=0,FunctionStopFlag=1;
						SetInterval(NumGet);
						NumGet=1,ReturnShowNum=1;
					}
					break;
				case 3:		//Run
					FunctionStopFlag=1,ReturnShowNum=1;
					FlowingFlag=1;
					break;
				case 4:		//Stop
					FunctionStopFlag=1,ReturnShowNum=1;
					FlowingFlag=0;
					break;
			}
			break;
		case 3:		//BackSet
			switch(CurrentPage[1])
			{
				case 0:
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 4:		//Picture
							Show_Function(2,1,1);
							if(Sure_Flag)
								Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=1;
							break;
					}
					break;
				case 1:			//BackGround
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 1:		//Origin
							FunctionStopFlag=1,ReturnShowNum=1;
							BackNum=0;
							MenuUpdateFlag[0]=0,MenuUpdateFlag[2]=2;
							break;
						case 2:		//Saved
//uint16_t BackGronudColor=WHITE;
//uint16_t RectColor=LIGHTBLUE;
//uint16_t StrColor=BLACK;
//MenuUpdateFlag[3]
							Show_Function(2,1,1);
							if(Sure_Flag)
								Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=1;
							break;
					}
					break;
				case 2:		//BackColor
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 1:		//WordColor
							Show_Function(3,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=1;
								StrColor=RGBColors[NumGet][1];
								MenuUpdateFlag[0]=0,MenuUpdateFlag[2]=2;
							}
							break;
						case 2:		//FramColor
							Show_Function(3,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=1;
								RectColor=RGBColors[NumGet][1];
								MenuUpdateFlag[0]=0,MenuUpdateFlag[2]=2;
							}
							break;
						case 3:		//BackColor
							Show_Function(3,1,1);
							if(Sure_Flag)
							{
								Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=1;
								BackGronudColor=RGBColors[NumGet][1];
								MenuUpdateFlag[0]=0,MenuUpdateFlag[2]=2;
							}
							break;
					}
					break;
				case 3:		//SaveMenu
					switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
					{
						case 1:		//Save
							FunctionStopFlag=1,ReturnShowNum=1;
							StorageData(4);
							break;
						case 2:		//Reset
							FunctionStopFlag=1,ReturnShowNum=1;
							BackGronudColor=WHITE;
							RectColor=LIGHTBLUE;
							StrColor=BLACK;
							StorageData(4);
							break;
					}
					break;
			}
			break;
		case 4:				//天气时钟部分，暂未开发
			switch(MenuPage[CurrentPage[0]][CurrentPage[1]].CurrentChoice)
			{
				case 1:
					FunctionStopFlag=1,ReturnShowNum=5;
					break;
				case 2:
					FunctionStopFlag=1,ReturnShowNum=5;
					break;
				case 3:
					Show_Function(5,1,1);
					if(Sure_Flag)
						Sure_Flag=0,FunctionStopFlag=1,ReturnShowNum=5;
					break;
			}
			break;
	}
	if(FunctionStopFlag)
	{
		NumGet=1;
		FunctionStopFlag=0;
		FunctionFlag=0;
		LCD_ReturnShow();
		MenuUpdateFlag[0]=1;
		MenuUpdateFlag[1]=1;
	}
}

