#include "led.h"
#include "delay.h"

    
//??DHT22
void DHT22_Rst(void)	   
{      	
    DHT22_DQ_OUT=0; 	//??DQ
    delay_ms(20);    	//????18ms
    DHT22_DQ_OUT=1; 	//DQ=1 
	delay_us(30);     	//????20~40us
}
//??DHT22???
//??1:????DHT22???
//??0:??
u8 DHT22_Check(void) 	   
{   
	u8 retry=100;
   	while ((!DHT22_DQ_IN)&&retry)//DHT22???40~80us
	{
		retry--;
		delay_us(1);
	};	 
	if(retry<1) return 1;
	else retry=100;
    while (DHT22_DQ_IN&&retry)//DHT22????????40~80us
	{
		retry--;
		delay_us(1);
	};
	if(retry<1) 
		return 1;	    
	return 0;
}
//?DHT22?????
//???:1/0
u8 DHT22_Read_Bit(void) 			 
{
 	u8 dat;
 	u8 retry=100;
	while((!DHT22_DQ_IN)&&retry)//???????
	{
		retry--;
		delay_us(1);
	}
	retry=100;
	dat=0;
	delay_us(30);//??30us
	if(DHT22_DQ_IN)	
		dat=1;	   
	while(DHT22_DQ_IN&&retry)//??????
	{
		retry--;
		delay_us(1);
	}
	return dat;		
}
//?DHT22??????
//???:?????
u8 DHT22_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT22_Read_Bit();
    }						    
    return dat;
}
//?DHT22??????
//temp:???(??:0~50°)
//humi:???(??:20%~90%)
//???:0,??;1,????

u8 DHT22_Read_Data(u8 *temp)    
{        
 	u8 buf[5];
	u8 i;
	DHT22_Rst();
	if(DHT22_Check()==0)
	{
		for(i=0;i<5;i++)//??40???
		{
			buf[i]=DHT22_Read_Byte();
		}
		//???????????????8?(????1?char,????????,????8?)
		if((unsigned char)(buf[0]+buf[1]+buf[2]+buf[3])==buf[4])  
		{
			for(i=0;i<4;i++)
			{
				*temp=buf[i];
				temp++;
			}
			return 0;	
		}
	}
	return 1;   
}
//³õÊ¼»¯DHT22µÄIO¿Ú DQ Í¬Ê±¼ì²âDHT22µÄ´æÔÚ
//??1:???
//??0:??    	 
u8 DHT22_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);		
	
	DHT22_Rst();
	return DHT22_Check();
}
