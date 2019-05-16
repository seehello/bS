#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY0 PCin(5)   	
#define KEY1 PAin(15)	 
#define WK_UP  PAin(0)	 
 

#define KEYOUT1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//读取按键0
#define KEYOUT2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//读取按键1
#define KEYOUT3  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键2 
#define KEYOUT4  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)//读取按键3

#define KEYIN1 PCout(4)
#define KEYIN2 PCout(5)
#define KEYIN3 PCout(6)
#define KEYIN4 PCout(7)

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//WK_UP  

#define outleft0 PAout(0)	
#define outleft1 PAout(1)	
#define outleft2 PAout(2)	
#define outleft3 PAout(3)	

#define inleft0 PAin(0)	
#define inleft1 PAin(1)	
#define inleft2 PAin(2)	
#define inleft3 PAin(3)
//上端引脚
#define inup4 PAin(4)	
#define inup5 PAin(5)	
#define inup6 PAin(6)	
#define inup7 PAin(7)	

#define outup4 PAout(4)	
#define outup5 PAout(5)	
#define outup6 PAout(6)	
#define outup7 PAout(7)	

void KEY_Init(void);//IO初始化
void init(void);
u8 KEY_Scan(u8 mode);  	//按键扫描函数		
void KEY_ch(u8 a);
void Read_KeyVaule(void);
#endif
