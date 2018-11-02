/**
  ******************************************************************************
  * @file    fifo.h
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Plik nag³ówkowy procedur kolejek fifo
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

#ifndef _FIFOBUF_H_
#define _FIFOBUF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#define U0RFIFOBUFFER FIFOBUFFER


/**
 * @brief struktura opisuj¹ca znakow¹ kolejkê fifo
 */
typedef struct _FIFOBuffer_s{
  char *BufferIn; //!< wskaŸnik do bufora ze znakami
  volatile unsigned int Count;//!< iloœæ znaków w buforze
  volatile unsigned int FirstItemPos;//!< pozycja pierwszego znaku licz¹c od pocz¹tku bufora
  volatile unsigned int Length;//!< d³ugoœæ bufora
}fifobuf_t;

/**
 * @brief struktura opisuj¹ca kolejkê fifo liczb int32
 */
typedef struct int32fifo_s{
	int32_t *items;
	uint32_t count;
	uint32_t firstitempos;
	uint32_t length;
}int32fifo_t;

/**
 * @brief struktura opisuj¹ca kolejkê fifo liczb uint16_t
 */
typedef struct u16fifo_s{
	volatile uint16_t *items;
	volatile uint32_t count;
	volatile uint32_t firstitempos;
	volatile uint32_t length;
}u16fifo_t;

/**
 * @brief amorficzna postac kolejki fifo
 */
typedef struct _afifobuffer_s{
	void *items;//!< wskaŸnik do bufora z elementami
	unsigned int itemlen;//!< d³ugoœæ pojedynczego elementu w bajtach
	unsigned int count;//!< liczba elementów w kolejce
	unsigned int firstitempos;//!< po³o¿enie pierwszego elementu licz¹c od pocz¹tku bufora
	unsigned int length;//!< d³ugoœæ bufora liczona elementami
}afifobuf_t;

/**
 * @brief zdejmuje z kolejki najstarszy element
 * @param buf - wskaznik do struktury kolejki
 * @param item - wskaznik do zdejmowanego elementu
 * @return 0 - kolejka jest pusta, 1 - element zostal zdjety
 */
char afifo_from(afifobuf_t *buf, void *item);

/**
 * @brief wstawia do kolejki kolejny element
 * @param buf - wskaznik do struktury kolejki
 * @param item - wskaznik do elementu wstawianego
 * @param Update: 0 - bez nadpisywania najstarszych elementow, 1 - z nadpisywaniem
 * @return 0 - element nie zostal wstawiony, 1 - przeciwnie
 */
char afifo_to(afifobuf_t *buf, void *item, char Update);

/**
 * @brief wstawia do kolejki amorficznej kolejny element,
 * przy pelnym zapelnieniu usuwajac najstarszy
 * @param buf - wskaznik do struktury kolejki
 * @param item - wskaznik do elementu wstawianego
 */
void afifo_to_update(afifobuf_t *buf, void * item);

/**
 * @brief probuje wstawic do kolejki amorficznej kolejny element,
 * jezeli kolejka niezapelniona
 * @param buf - wskaznik do struktury kolejki
 * @param item - wskaznik do elementu wstawianego
 * @return 0 - element nie zostal wstawiony, 1 - przeciwnie
 */
char afifo_to_no_update(afifobuf_t *buf, void * item);

/**
 * @brief oproznia kolejke
 * @param buf - wskaznik do struktury kolejki
 */
void afifo_flush(afifobuf_t *buf);

/**
 * @brief inicjuje kolejke fifo
 * @param FIFOBuf - wskaznik do kolejki
 * @param Buf - wskaznik do bufora z elementami kolejki
 * @param Length - dlugosc bufora
 */
void FIFOBufInit(fifobuf_t *FIFOBuf, char *Buf,unsigned int Length);

/**
 * @brief szuka sekwencji znakow str
 * @param buf - kolejka fifo
 * @param str - string ze znakami
 * @param pos - pozycja pierwszego znaku stringu w kolejce
 * @return 0 - nie znaleziono, 1 - znaleziono
 */
char FIFOstrstr(fifobuf_t *buf, const char *str, unsigned int *pos);

char int32fifo_to_update(int32fifo_t *buf, int32_t item);
char ToFIFOBuf(fifobuf_t *Buf, char Item, char Update);
char ReadFromFIFOBuf(fifobuf_t *Buf, unsigned int Pos);
void afifo_read(afifobuf_t *buf, unsigned int Pos, void *item);
char FromFIFOBuf(fifobuf_t *Buf);
void FlushFIFOBuf(fifobuf_t *Buf);
uint16_t u16fifo_read(u16fifo_t * buf, uint32_t Pos, uint16_t item);
char u16fifo_to(u16fifo_t *buf, uint16_t item, char update);
char u16fifo_to_update(u16fifo_t *buf, uint16_t item);
char u16fifo_to_no_update(u16fifo_t *buf, uint16_t item);
uint16_t u16fifo_from(u16fifo_t *buf);

#ifdef __cplusplus
}
#endif

#endif
