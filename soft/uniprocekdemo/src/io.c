/**
 * @file    io.c
 * @author  Miroslaw Lach
 * @version V1.0
 * @date    16.02.2012
 * @brief   Ustawienia linii portów
 *
 * <h2><center> &copy; COPYRIGHT 2012 Miroslaw Lach</center></h2>
 */

#include "procfamily.h"
#include "io.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
						RCC_APB2Periph_GPIOC |
						RCC_APB2Periph_GPIOB |
						RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
//JTAG off
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

//GP output PP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;


//GP output PP, 50MHz
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = PB8_Pin;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//output AF_PP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = PA2_Pin;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//output AF_PP, 50MHz
	//inputs
	//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

//inputs floating
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;



}

