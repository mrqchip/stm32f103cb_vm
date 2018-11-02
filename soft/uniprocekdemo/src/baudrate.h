#ifndef _BAUDRATE_H_
#define _BAUDRATE_H_

//#define BAUDRATE96008N1
//#define BAUDRATE192008N1
//#define BAUDRATE384008N1
#define BAUDRATE1152008N1
#if defined(BAUDRATE96008N1)
extern const USART_InitTypeDef Usart96008N1Params;
#endif
#if defined(BAUDRATE192008N1)
extern const USART_InitTypeDef Usart192008N1Params;
#endif
#if defined(BAUDRATE384008N1)
extern const USART_InitTypeDef Usart384008N1Params;
#endif
#if defined(BAUDRATE1152008N1)
extern const USART_InitTypeDef Usart1152008N1Params;
#endif

#endif //_BAUDRATE_H_
