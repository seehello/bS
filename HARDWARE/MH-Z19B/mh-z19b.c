#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "stm32f10x_gpio.h"
#include "mh-z19b.h"

int  CO2Data;
u8   USART1Count;
//���崮�ڷ�������
uint16_t  CO2TxBuffer[9]={0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
uint16_t  USART_RX_BUF_2[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


/*******************************************************************************
* �� �� ��         : CO2_Tx
* ��������                     : ���ڷ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void CO2_Tx()
{
        int i;
  for(i = 0; i < 9; i++) 
   { 
                        USART_ClearFlag(USART2, USART_FLAG_TC);
                        USART_SendData(USART2, CO2TxBuffer[i]);  
                        while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);  
   }
}
/*******************************************************************************
* �� �� ��         : CheckSum
* ��������                     : У��ͺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void CheckSum()
{
         char i,checksum=0;
                 for( i = 1; i < 8; i++)  
                        {  
                                checksum += USART_RX_BUF_2[i];  
                         } 
                         checksum = 0xff - checksum;  
                        checksum += 1;                                         
                                if(checksum == USART_RX_BUF_2[8])        
                                CO2Data = USART_RX_BUF_2[2] * 256 + USART_RX_BUF_2[3]; 
                                if(CO2Data > 9999)
                                CO2Data=0;                                                           
                               printf("CO2 = %d ppm   \n", CO2Data);
															 printf("\r");
}
/*******************************************************************************
* �� �� ��         : USART2_IRQHandler
* ��������                     : ����ͨ���жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
        {          
          USART_ClearFlag(USART2 , USART_FLAG_RXNE);
					USART_RX_BUF_2[USART1Count++] = USART2->DR;
        }
     if(USART1Count>=9)
		 {
        USART1Count=0;
		 }
}



