/**
 ******************************************************************************
 * @file    serialcomm.h
 * @author  Miroslaw Lach
 * @version V.1.0
 * @date    09.02.2012
 * @brief   Plik nag³ówkowy procedur portu szeregowego
 ******************************************************************************
 *
 * @copyright
 *
 *
 * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
 */

#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

#include "fifobuf.h"
#include "procfamily.h"
/**
 * @brief struktura opisuj¹ca port szeregowy
 */
typedef struct serialcomm_s{
	USART_TypeDef *usart; //!< 	 wskaznik do sprzetu portu szeregowego
	fifobuf_t *fifo_rx; //!< wskaznik do bufora nadawczego
	fifobuf_t *fifo_tx; //!< wskaznik do bufora odbiorczego
}serialcomm_t;

/**
 * @brief wyrzut stanu pamieci na wskazany port
 * @par ser - wskaŸnik do struktury portu szeregowego
 * @par mem - adres poczatkowy pamieci
 * @par size - ile bajtow
 */
void DumpMemory(serialcomm_t *ser, char *mem, int size);

/**
 * @brief wyrzut stanu pamieci na wskazany port slowa 16-bit
 * @par ser - wskaŸnik do struktury portu szeregowego
 * @par mem - adres poczatkowy pamieci
 * @par size - ile slow 16-bit
 */
void DumpMemory16b(serialcomm_t *ser, char *mem, int size);

/**
 * @brief zdjêcie najstarszego znaku z kolejki odbiorczej , funkcja nie sprawdza liczby znakow w kolejce
 * @par ser - wskaznik do struktury
 * @return zdjety znak
 * @see serialcomm_t
 */
char serialcomm_fromr_b(serialcomm_t *ser);

/**
 * @brief odczyt znaku z kolejki odbiorczej z pozycji Pos, funkcja nie sprawdza liczby znakow w kolejce
 * @par ser wskaznik do struktury
 * @par Pos pozycja znaku w kolejce
 * @return odebrany znak
 * @see serialcomm_t
 */
char serialcomm_read_b(serialcomm_t * ser, unsigned int Pos);

/**
 * @brief wysylanie jednego znaku do kolejki nadawczej
 * @par ser wskaznik do struktury
 * @par c wysylany znak
 * @see serialcomm_t
 */
void serialcomm_sendt_b(serialcomm_t *ser, char c);

/**
 * @brief wysylanie napisu do kolejki nadawczej
 * @par ser: wskaznik do struktury
 * @par buf: wskzaznik do napisu
 * @see serialcomm_t
 */
void serialcomm_send_str(serialcomm_t *ser, char *buf);

/**
 * @brief wysylanie pary znakow konca linii [CR][LF]
 * @par ser: wskaznik do struktury
 * @see serialcomm_t
 */
void serialcomm_send_strLn0(serialcomm_t *ser);

/**
 * @brief wysylanie napisu do kolejki nadawczej i znakow konca linii
 * @par ser: wskaznik do struktury
 * @par buf: wskzaznik do napisu
 * @see serialcomm_t
 */
void serialcomm_send_strLn(serialcomm_t *ser, char *buf);

/**
 * @brief wysylanie ci¹gu len bajtów do kolejki nadawczej
 * @par ser: wskaznik do struktury komunikacyjnej
 * @par buf: wskaŸnik do ci¹gu bajtów
 * @par len: liczba bajtów
 * @see serialcomm_t
 */
void serialcomm_send_len(serialcomm_t *ser, char *buf, unsigned int len);

#endif /* SERIALCOMM_H_ */
