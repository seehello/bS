#ifndef _mq135adc_H
#define _mq135adc_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

#define ADC1_DR_Address ((u32)0x4001244c);

void mq135adc_init(void);

#endif
