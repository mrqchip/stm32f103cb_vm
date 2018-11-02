/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32F10x Standard Peripherals Library
**
**  Distribution: The file is distributed "as is", without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. This file may only be built (assembled or compiled and linked)
**  using the Atollic TrueSTUDIO(R) product. The use of this file together
**  with other tools than Atollic TrueSTUDIO(R) is not permitted.
**
*****************************************************************************
*/

/* Includes */
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include "procfamily.h"
#include "timers.h"
#include "io.h"
#include "usart_diag.h"
#include "crc32.h"
#include "interrupt.h"
#include "progpres.h"
#include "adc.h"
#include "dma.h"
#include "screw.h"
#include "nonvolconfig.h"
#include "butterworth.h"
#include "mainproc.h"


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	SystemCoreClockUpdate();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	CRC_Configuration();
	TIM4_Configuration();
	TIM2_Configuration();
	GPIO_Configuration();
	USARTdiag_Configuration();
	NVIC_Configuration();
	ProgramPresentation();
	LoadAppConfiguration();
	SetPWMpa2();
  /* Infinite loop */
  while (1)
  {
	  MainProcess();
  }
}

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func, const char *failedexpr)
{
  while(1)
  {}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr)
{
   __assert_func (file, line, NULL, failedexpr);
}

#ifdef USE_SEE
#ifndef USE_DEFAULT_TIMEOUT_CALLBACK
/**
  * @brief  Basic management of the timeout situation.
  * @param  None.
  * @retval sEE_FAIL.
  */
uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* Return with error code */
  return sEE_FAIL;
}
#endif
#endif /* USE_SEE */

