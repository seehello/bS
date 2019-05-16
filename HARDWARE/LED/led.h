#ifndef __DHT22_H
#define __DHT22_H 
#include "sys.h"   

////IO????											   
#define	DHT22_DQ_OUT PAout(0) //????	PA0 
#define	DHT22_DQ_IN  PAin(0)  //????	PA0

u8 DHT22_Init(void);			//???DHT22
u8 DHT22_Read_Data(u8 *temp);	//?????
u8 DHT22_Read_Byte(void);		//??????
u8 DHT22_Read_Bit(void);		//?????
u8 DHT22_Check(void);			//??????DHT22
void DHT22_Rst(void);			//??DHT22    
#endif
