#ifndef _mhz19b_H
#define _mhz19b_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"


void CO2_Tx(void);
void CheckSum(void);

#endif
