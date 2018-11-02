/**
  ******************************************************************************
  * @file    serialcomm.c
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Procedury portu szeregowego
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

#include <stdio.h>
#include "serialcomm.h"


#include "fifobuf.h"
#include "ascii.h"
#define pserial(s) ((serialcomm_t *) s)


void serialcomm_sendt_b(serialcomm_t *ser, char c){
	while (ser->fifo_tx->Count >= ser->fifo_tx->Length);
	USART_ITConfig(ser->usart,USART_IT_TXE,DISABLE);
	ToFIFOBuf(ser->fifo_tx,c,0);
	USART_ITConfig(ser->usart,USART_IT_TXE,ENABLE);
}

void serialcomm_send_str(serialcomm_t *ser, char *buf){
	for(; *buf != 0 ; buf++)
	{
		serialcomm_sendt_b(ser,*buf);
	}
}

void serialcomm_send_strLn0(serialcomm_t *ser){
	serialcomm_send_str(ser, (char *)NewLineMsg);
}

void serialcomm_send_strLn(serialcomm_t *ser, char *buf){
	serialcomm_send_str(ser,buf);
	serialcomm_send_strLn0(ser);
}

void serialcomm_send_len(serialcomm_t *ser, char *buf, unsigned int len){
	while( len--){
		serialcomm_sendt_b(ser,*buf);
		buf++;
	}
}

char serialcomm_read_b(serialcomm_t *ser, unsigned int Pos){
	char Result;
	USART_ITConfig(ser->usart,USART_IT_RXNE,DISABLE);
	Result = ReadFromFIFOBuf(ser->fifo_rx,Pos);
	USART_ITConfig(ser->usart,USART_IT_RXNE,ENABLE);
	return Result;
}

char serialcomm_fromr_b(serialcomm_t *ser){
	char Result;
	USART_ITConfig(ser->usart,USART_IT_RXNE,DISABLE);
	Result = FromFIFOBuf(ser->fifo_rx);
	USART_ITConfig(ser->usart,USART_IT_RXNE,ENABLE);
	return Result;
}

/*
 * @brief wyrzut stanu pamieci na wskazany port
 * @par ser - wskaünik do struktury portu szeregowego
 * @par mem - adres poczatkowy pamieci
 * @par size - ile bajtow
 */
void DumpMemory(serialcomm_t *ser, char *mem, int size){
	int i;
	char buf[32];
	serialcomm_send_str(ser,"Dump Memory [");
	i=(int)mem;
	sprintf(buf,"0x%08X]{\r\n",i);
	serialcomm_send_strLn(ser,buf);
	for (i=0 ; i < size ; i++){
		sprintf(buf,"%02X ",(int)*mem);
		serialcomm_send_str(ser,buf);
		if (i % 16 == 15){
			serialcomm_send_strLn0(ser);
		}
		mem++;
	}
	if (i % 16 != 0)
		serialcomm_send_strLn0(ser);
	serialcomm_send_strLn(ser,"}");
}

/*
 * @brief wyrzut stanu pamieci na wskazany port slowa 16-bit
 * @par ser - wskaünik do struktury portu szeregowego
 * @par mem - adres poczatkowy pamieci
 * @par size - ile slow 16-bit
 */
void DumpMemory16b(serialcomm_t *ser, char *mem, int size){
	int i;
	char buf[32];
	serialcomm_send_str(ser,"Dump Memory [");
	i=(int)mem;
	sprintf(buf,"0x%08X]{\r\n",i);
	serialcomm_send_strLn(ser,buf);
	for (i=0 ; i < size ; i++){
		sprintf(buf,"%04hX ",(uint16_t)*mem);
		serialcomm_send_str(ser,buf);
		if (i % 8 == 7){
			serialcomm_send_strLn0(ser);
		}
		mem+=2;
	}
	if (i % 8 != 0)
		serialcomm_send_strLn0(ser);
	serialcomm_send_strLn(ser,"}");
}

