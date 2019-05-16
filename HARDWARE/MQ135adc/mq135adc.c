#include "mq135adc.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"

volatile u16 ADC_ConvertedValue;

void mq135adc_init()
{
	GPIO_InitTypeDef GPIO_InitStructure; //����GPIO����
	ADC_InitTypeDef ADC_InitStructure; //����ADCģ��ת��
	DMA_InitTypeDef DMA_InitStructure; //����DMAֱ�Ӵ�ȡ
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//ʹ��GPIOC��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ADC1ʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);//DMAʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//�������� ģʽ����
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//PC1 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//  
	//ʹ��DMA
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;	 	//ADC��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;		 	//�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;    //���� ���ڴ浽����
	DMA_InitStructure.DMA_BufferSize = 1;                 //�������ݵĴ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  		//�ڴ��ַ�̶�
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//�������ݵ�λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //�ڴ����ݵ�λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		 //DMA����ģʽ ѭ������
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//���ȼ� ��
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;       //��ֹ�ڴ浽�ڴ�Ĵ���
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);       //����DMA ͨ��1
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//ʹ��ADC
	//ADC_DeInit(ADC1);  //��λADC1 Ĭ��ֵ ��Ϊȱʡ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//����ADCģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;				//��ֹɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//��������ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//��ʹ���ⲿ����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//�ɼ������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//Ҫת����ͨ����Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	
	
	ADC_Cmd(ADC1, ENABLE);	//
	ADC_DMACmd(ADC1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); //����ADC��Ƶ����8 72M/8=9
	
	//��������ת��ͨ����55.5����������
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);	//1��ͨ��ת��һ�κ�ʱ21us 4��ͨ��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5);	//��������ADC_SAMPLE_NUM
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5);	//�ܹ���ʱ4*21*ADC_SAMPLE_NUM��64��=5.4ms<10ms
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);//ADC1ͨ��11 ��������55.5
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}

