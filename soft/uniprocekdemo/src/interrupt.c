/**
  ******************************************************************************
  * @file    SysTick/SysTick_Example/stm32f0xx_it.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    16-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "procfamily.h"
#include "timers.h"
#include "usart_diag.h"
#include "nonvolconfig.h"
#include "io.h"
#include "interrupt.h"

void NVIC_Configuration(void){
	NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the UARTdiag global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USARTdiag_IRQn;
#if defined (STM32F10X_HD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_MD)
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
#endif
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void TIM2_IRQHandler(void){
/*  funkcja TIM_GetITStatus
	itstatus = TIMx->SR & TIM_IT;

	itenable = TIMx->DIER & TIM_IT;
	if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
	{
	bitstatus = SET;
	}
	else
	{
	bitstatus = RESET;
	}
	return bitstatus;*/
/*  Funkcja TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
 *   TIMx->SR = (uint16_t)~TIM_IT;
 *
 */
	if ((TIM2->SR & TIM_IT_Update) && (TIM2->DIER & TIM_IT_Update)){//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		TIM2->SR = (uint16_t)~TIM_IT_Update;//TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

void TIM3_IRQHandler(void){
/*  funkcja TIM_GetITStatus
	itstatus = TIMx->SR & TIM_IT;

	itenable = TIMx->DIER & TIM_IT;
	if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
	{
	bitstatus = SET;
	}
	else
	{
	bitstatus = RESET;
	}
	return bitstatus;*/
/*  Funkcja TIM_ClearITPendingBit(TIM_TypeDef* TIMx, uint16_t TIM_IT)
 *   TIMx->SR = (uint16_t)~TIM_IT;
 *
 */
	if ((TIM3->SR & TIM_IT_Update) && (TIM3->DIER & TIM_IT_Update)){//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		TIM3->SR = (uint16_t)~TIM_IT_Update;//TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		GPIOB->BRR = PB8_Pin;
		GPIOB->BSRR = PB8_Pin;
	}

}

void TIM4_IRQHandler(void){
	uint32_t i;
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET){
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		for (i=0 ; i<TIMERS1MS_LOT ; i++){
			if (Timers1ms[i]>0){
				Timers1ms[i]--;
			}
		}
	}

}
/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  RefreshTimers1ms();
}

void USART3_IRQHandler(void)
{
	if (USART_GetITStatus(USARTdiag,USART_IT_TXE) != RESET){
		if (sUDiagTBuf.Count>0){
			USART_SendData(USARTdiag,FromFIFOBuf(&sUDiagTBuf));
		}else{
			USART_ITConfig(USARTdiag,USART_IT_TXE,DISABLE);
		}
	}
	if (USART_GetITStatus(USARTdiag,USART_IT_RXNE) != RESET){
		ToFIFOBuf(&sUDiagRBuf,USART_ReceiveData(USARTdiag),0);
	}
}

/*void EXTI15_10_IRQHandler(void){
	#if defined (STM32F10X_HD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_XL)
	  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	  {
	    // Toggle LED2
	     STM_EVAL_LEDToggle(LED2);

	    // Clear the  EXTI line 8 pending bit
	    EXTI_ClearITPendingBit(EXTI_Line8);
	  }
	#else
	  if(EXTI_GetITStatus(EXTI_Line13) != RESET){
		  MainPTimer=AppConfig.PauseRZ13;
		  EXTI_ClearITPendingBit(EXTI_Line13);
	  }
	#endif

}*/

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
