#include "stm32f10x.h"
#include "baudrate.h"

#if defined(BAUDRATE96008N1)
const USART_InitTypeDef Usart96008N1Params={
		  .USART_BaudRate=9600,
		  .USART_WordLength=USART_WordLength_8b,
		  .USART_StopBits=USART_StopBits_1,
		  .USART_Parity=USART_Parity_No,
		  .USART_Mode=USART_Mode_Tx | USART_Mode_Rx,
		  .USART_HardwareFlowControl=USART_HardwareFlowControl_None,
};
#endif
#if defined(BAUDRATE192008N1)
const USART_InitTypeDef Usart192008N1Params={
		  .USART_BaudRate=19200,
		  .USART_WordLength=USART_WordLength_8b,
		  .USART_StopBits=USART_StopBits_1,
		  .USART_Parity=USART_Parity_No,
		  .USART_Mode=USART_Mode_Tx | USART_Mode_Rx,
		  .USART_HardwareFlowControl=USART_HardwareFlowControl_None,
};
#endif
#if defined(BAUDRATE384008N1)
const USART_InitTypeDef Usart384008N1Params={
		  .USART_BaudRate=38400,
		  .USART_WordLength=USART_WordLength_8b,
		  .USART_StopBits=USART_StopBits_1,
		  .USART_Parity=USART_Parity_No,
		  .USART_Mode=USART_Mode_Tx | USART_Mode_Rx,
		  .USART_HardwareFlowControl=USART_HardwareFlowControl_None,
};
#endif
#if defined(BAUDRATE1152008N1)
const USART_InitTypeDef Usart1152008N1Params={
		  .USART_BaudRate=115200,
		  .USART_WordLength=USART_WordLength_8b,
		  .USART_StopBits=USART_StopBits_1,
		  .USART_Parity=USART_Parity_No,
		  .USART_Mode=USART_Mode_Tx | USART_Mode_Rx,
		  .USART_HardwareFlowControl=USART_HardwareFlowControl_None,
};
#endif
