
#include "procfamily.h"
#include "dma.h"

void ADC_Configuration(void){
	ADC_InitTypeDef ADC_InitStructure;
	//clock for ADC (max 14MHz --> 24/2=12MHz)
	RCC_ADCCLKConfig (RCC_PCLK2_Div2);
	// enable ADC system clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = ADC_CHANNELS_NMBR;
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//Uc0
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,2,ADC_SampleTime_239Cycles5);//Uc1

    ADC_TempSensorVrefintCmd(ENABLE);
    ADC_DMACmd(ADC1,ENABLE);
    ADC_Cmd(ADC1,ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}


