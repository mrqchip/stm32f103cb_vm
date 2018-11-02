#ifndef _DMA_H_
#define _DMA_H_

#include "adc.h"
void DMA_Configuration(void);

extern __IO uint16_t ADCVal[ADC_CHANNELS_NMBR];

#endif
