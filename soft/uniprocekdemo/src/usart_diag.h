#ifndef _USART_DIAG_H__
#define _USART_DIAG_H__
#include "fifobuf.h"
#include "serialcomm.h"

#define USARTdiag USART3
#define USARTdiag_IRQn USART3_IRQn
#define RCC_APBPeriph_USARTDiag RCC_APB1Periph_USART3
#define USARTDiag_RCC_APBPeriphClockCmd RCC_APB1PeriphClockCmd

#define UDIAGTBUF 512
#define UDIAGRBUF 16


extern char                  UDiagTBuf[UDIAGTBUF];
extern fifobuf_t              sUDiagTBuf;
extern char                  UDiagRBuf[UDIAGRBUF];
extern fifobuf_t              sUDiagRBuf;
extern const serialcomm_t DiagComm;

void BufUnvisibleCharToDiag(char *buf);
char FromUDiagRBuffer(void);
void MsgToUDiag(char *Msg);
void MsgToUDiagLn(char *Msg);
void MsgToUDiagLn0(void);
void ToUDiagTBuffer(char c);
void USARTdiag_Configuration(void);
char ReadUDiagRBuffer(unsigned int Pos);
void DumpMemoryToUDiag(char *mem, int size);

#endif
