/**
  ******************************************************************************
  * @file    usart_diag.c
  * @author  Miroslaw Lach
  * @version V2.0
  * @date    18.08.2011
  * @brief   procedury diagnostycznego portu szeregowego
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, AUTHOR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "procfamily.h"
#include "usart_diag.h"
#include "ascii.h"
#include "serialcomm.h"
#include "io.h"
#include "baudrate.h"

char                    UDiagTBuf[UDIAGTBUF];
fifobuf_t                sUDiagTBuf={
		  //char *BufferIn;
		.BufferIn=UDiagTBuf,
		  //unsigned int Count;
		.Count=0,
		  //unsigned int FirstItemPos;
		.FirstItemPos=0,
		  //unsigned int Length;
		.Length=UDIAGTBUF

};

char                    UDiagRBuf[UDIAGRBUF];
fifobuf_t                sUDiagRBuf={
		  //char *BufferIn;
		.BufferIn=UDiagRBuf,
		  //unsigned int Count;
		.Count=0,
		  //unsigned int FirstItemPos;
		.FirstItemPos=0,
		  //unsigned int Length;
		.Length=UDIAGRBUF

};

const serialcomm_t DiagComm={
		.usart=USARTdiag,
		.fifo_rx=&sUDiagRBuf,
		.fifo_tx=&sUDiagTBuf,
};




char ReadUDiagRBuffer(unsigned int Pos){
	return serialcomm_read_b((void *)&DiagComm,Pos);
}

void ToUDiagTBuffer(char c)
{
	serialcomm_sendt_b((void*)&DiagComm,c);
}

char FromUDiagRBuffer(void)
{
	return serialcomm_fromr_b((void *)&DiagComm);
}

void MsgToUDiag(char *Msg)
{
	serialcomm_send_str((void *)&DiagComm,Msg);
}

void MsgToUDiagLn0(void)
{
	serialcomm_send_strLn0((void *)&DiagComm);
}

void MsgToUDiagLn(char *Msg)
{
	serialcomm_send_strLn((void *)&DiagComm,Msg);
}

void USARTdiag_Configuration(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	  /* Enable GPIO clock */

	  /* Enable USART clock */
	USARTDiag_RCC_APBPeriphClockCmd(RCC_APBPeriph_USARTDiag, ENABLE);
#if defined (STM32F030C6T6)
	  /* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(DIAG_TXD_GPIO, DIAG_TXD_PinSource, DIAG_TXD_GPIO_AF);

	  /* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(DIAG_RXD_GPIO, DIAG_RXD_PinSource, DIAG_RXD_GPIO_AF);

	  /* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = DIAG_TXD_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DIAG_TXD_GPIO, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = DIAG_RXD_Pin;
	GPIO_Init(DIAG_RXD_GPIO, &GPIO_InitStructure);
#endif
#if defined (STM32F10X_HD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_MD)
//output AF_PP
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//output AF_PP, 50MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

// USARTdiag TxD
	GPIO_InitStructure.GPIO_Pin = DIAG_TXD_Pin;
	GPIO_Init(DIAG_TXD_GPIO, &GPIO_InitStructure);
//inputs, 50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;

	// USARTdiag RxD
	GPIO_InitStructure.GPIO_Pin = DIAG_RXD_Pin;
	GPIO_Init(DIAG_RXD_GPIO, &GPIO_InitStructure);
#endif
	  /* USART configuration */
	USART_Init(USARTdiag, (USART_InitTypeDef *)&Usart1152008N1Params);

	USART_ITConfig(USARTdiag,USART_IT_RXNE,ENABLE);
	  /* Enable USART */
	USART_Cmd(USARTdiag, ENABLE);
}

void DumpMemoryToUDiag(char *mem, int size){
	DumpMemory((serialcomm_t *)&DiagComm,mem,size);
}

/**
 * @brief wysylanie na port diagnostyczny ciagu znakow zakonczonych zerem zawierajacych znaki niedrukowalne
 * tlumaczone na znaczenie w kodzie ASCII
 * @par buf - wskaznik do bufora ze znakami
 */
void BufUnvisibleCharToDiag(char *buf){
	char tmp[8];
	for (; *buf!=0; buf++){
		ASCIIConvertUnVisibleChar(tmp,*buf);
		MsgToUDiag(tmp);
	}
}

