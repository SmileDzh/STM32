#ifndef __ADC_H_
#define __ADC_H_
#include "stm32f4xx.h"

void ADCInit(void);
u16 Get_ADC_Value(u8 ch,u8 times);
#endif

