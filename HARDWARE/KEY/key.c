#include "key.h"
#include "delay.h" 
#include "led.h"


//������ʼ������ 
//PA15��PC5 ���ó�����
GPIO_InitTypeDef GPIO_InitStructure;
u8 t;
	
void KEY_Init(void)
{
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTAʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PC15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
	
} 


void init(void)
{
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//PC15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}


void Read_KeyVaule(void)
{
	if(inup4==1)
	{
		delay_ms(10);//����
		if(inup4==1)
		{
			init();
			if(inleft0==1) t=1;
			else if(inleft1==1) t=5;
			else if(inleft2==1) t=9;
			else if(inleft3==1) t=13;			
		}
		KEY_Init();
	}
	else if(inup5==1)
	{
		delay_ms(10);
		if(inup5==0)
		{
			init();
			if(inleft0==1)t=2;
			else if(inleft1==1)t=6;
			else if(inleft2==1)t=10;
			else if(inleft3==1)t=14;			
		}
		KEY_Init();
  }
	else	if(inup5==1)
	{
		delay_ms(10);
		if(inup5==1)
		{
			init();
			if(inleft0==1)t=3;
			else if(inleft1==1)t=7;
			else if(inleft2==1)t=11;
			else if(inleft3==1)t=15;			
		}
		KEY_Init();
  }
	else	if(inup5==1)
	{
		delay_ms(10);
		if(inup5==1)
		{
			init();
			if(inleft0==1)t=4;
			else if(inleft1==1)t=8;
			else if(inleft2==1)t=12;
			else if(inleft3==1)t=16;			
		}
		KEY_Init();
  }
	
}

//void Read_KeyVaule(void)
//{
//	 u8 KeyVaule = 0;
//	if((GPIO_ReadInputData(GPIOA)&0XFF)!=0X0F)
//	{
//		delay_ms(10);
//		if((GPIO_ReadInputData(GPIOA)&0XFF)!=0X0F)
//		{
//			GPIO_SetBits(GPIOA,GPIO_Pin_0);
//			GPIO_ResetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0XFF)
//			{
//				case 0x11:KeyVaule=1;break;
//			  case 0x21:KeyVaule=5;break;
//			  case 0x41:KeyVaule=9;break;
//			  case 0x81:KeyVaule=13;break;
//			}
//			GPIO_SetBits(GPIOA,GPIO_Pin_1);
//			GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0XFF)
//			{
//				case 0x12:KeyVaule=2;break;
//			  case 0x22:KeyVaule=6;break;
//			  case 0x42:KeyVaule=10;break;
//			  case 0x82:KeyVaule=14;break;
//			}
//			GPIO_SetBits(GPIOA,GPIO_Pin_2);
//			GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3);
//			switch(GPIO_ReadInputData(GPIOA)&0XFF)
//			{
//				case 0x13:KeyVaule=3;break;
//			  case 0x23:KeyVaule=7;break;
//			  case 0x43:KeyVaule=11;break;
//			  case 0x83:KeyVaule=15;break;
//			}
//			GPIO_SetBits(GPIOA,GPIO_Pin_3);
//			GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5);
//			switch(GPIO_ReadInputData(GPIOA)&0XFF)
//			{
//				case 0x14:KeyVaule=4;break;
//			  case 0x24:KeyVaule=8;break;
//			  case 0x44:KeyVaule=45;break;
//			  case 0x84:KeyVaule=16;break;
//			}
//      GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
//	    GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
//			while((GPIO_ReadInputData(GPIOA)&0XFF)!=0X0F);
//			
//		}
//		t = KeyVaule;
//	}
//}



void KEY_ch(u8 a)
{
	KEY_Init();

	if(a == 1)
	{
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PC15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	}
	if(a == 2)
	{
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	}
	if(a == 3)
	{
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PC15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	}
	if(a == 4)
	{
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PC15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15
	}
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEYOUT1==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	     
	return 0;// �ް�������
}
