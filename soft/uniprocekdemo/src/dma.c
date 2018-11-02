
#include <stdint.h>
#include "stm32f10x.h"
#include "adc.h"
#include "dma.h"
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
__IO uint16_t ADCVal[ADC_CHANNELS_NMBR];

void DMA_Configuration(void){
	DMA_InitTypeDef DMA_InitStruct;

	DMA_DeInit(DMA1_Channel1);

	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr=ADC1_DR_Address;
	DMA_InitStruct.DMA_MemoryBaseAddr=(uint32_t)&ADCVal;
	DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA_InitStruct.DMA_BufferSize=ADC_CHANNELS_NMBR;
	DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode= DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority=DMA_Priority_High;
	DMA_InitStruct.DMA_M2M=DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	DMA_Cmd(DMA1_Channel1,ENABLE);
}
