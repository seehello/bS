#include "mq135adc.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"

volatile u16 ADC_ConvertedValue;

void mq135adc_init()
{
	GPIO_InitTypeDef GPIO_InitStructure; //配置GPIO引脚
	ADC_InitTypeDef ADC_InitStructure; //配置ADC模数转换
	DMA_InitTypeDef DMA_InitStructure; //配置DMA直接存取
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//使能GPIOC的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC1时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//输入引脚 模式悬空
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PC1 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//  
	//使能DMA
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 	//ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;		 	//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    //方向 从内存到外设
	DMA_InitStructure.DMA_BufferSize = 1;                 //传输内容的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  		//内存地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//外设数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //内存数据单位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		 //DMA工作模式 循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//优先级 高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       //禁止内存到内存的传输
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);       //配置DMA 通道1
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//使能ADC
	//ADC_DeInit(ADC1);  //复位ADC1 默认值 设为缺省
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;				//禁止扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//开启连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//要转换的通道数目
	ADC_Init(ADC1, &ADC_InitStructure);	
	
	ADC_Cmd(ADC1, ENABLE);	//
	ADC_DMACmd(ADC1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); //设置ADC分频因子8 72M/8=9
	
	//配置连续转换通道，55.5个采样周期
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);	//1个通道转换一次耗时21us 4个通道
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);	//采样个数ADC_SAMPLE_NUM
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);	//总共耗时4*21*ADC_SAMPLE_NUM（64）=5.4ms<10ms
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);//ADC1通道11 采样周期55.5
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}

