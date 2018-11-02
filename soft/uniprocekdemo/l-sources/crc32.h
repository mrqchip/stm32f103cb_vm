/**
  ******************************************************************************
  * @file    crc32.h
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Plik nag³ówkowy procedur zwi¹zanych z obliczaniem CRC-32
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

#ifndef _CRC32_H_
#define _CRC32_H_

#ifdef __cplusplus
extern "C" {
#endif


uint32_t CalculateCRC32(char *buf, int size);
void CRC_Configuration(void);


#ifdef __cplusplus
}
#endif


#endif
