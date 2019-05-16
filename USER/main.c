#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "dht22.h"
#include "stm32f10x_gpio.h"
#include "mh-z19b.h"
#include "mq135adc.h"

float tem=0,hum=0;
extern __IO u16 ADC_ConvertedValue;

float ADC_ConvertedValueLocal;
float AirQuality;
float AirQuality2;

#define MAX_CONVERTED_VALUE 4095
#define VREF                3300

void GPIO_init()
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级2
	uart_init(9600);//波特率9600
	DHT22_Init();
	mq135adc_init();
	
}
	

//void mhz19_read(void)
//{

//        while(1)
//        {
//            CO2_Tx();
//            delay_ms(1000);// 延时1000ms
//            CheckSum();
//         }
//}

int main(void)
{
	//delay_init();            //延时程序初始化
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断优先级2
  //LED_Init();
  //uart_init(9600);//波特率9600
	//Usart2_Init(9600);
	//DHT22_Init();
	
	GPIO_init();
	
	while(1)
	{
//		CO2_Tx();
//		DHT22_Read_Data(&tem,&hum);
//		delay_ms(1000);// 延时1000ms
//		CheckSum();
//		printf("TEMPURE = %f    \n\r",tem);
		
		
		ADC_ConvertedValueLocal = (float)ADC_ConvertedValue/4096*3.3;
		
		AirQuality = ((float)((float)ADC_ConvertedValue * VREF)/MAX_CONVERTED_VALUE);
		
		//AirQuality2 = AirQuality/1000;
		
		printf("nh4= %f \n",AirQuality);
		delay_ms(1000);
		printf("\r\n");
	}
	 //mhz19_read();
	
}


