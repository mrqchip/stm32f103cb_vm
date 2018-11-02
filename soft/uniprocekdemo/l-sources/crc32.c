/**
 ******************************************************************************
 * @file    crc32.c
 * @author  Miroslaw Lach
 * @version V1.0
 * @date    01.02.2012
 * @brief   procedury zwi¹zane z obliczaniem CRC-32
 ******************************************************************************
 * @copyright
 *
 *
 * <h2><center>&copy; COPYRIGHT 2012 Miroslaw Lach</center></h2>
 */

#include <stdint.h>
#include "procfamily.h"

/**
 * @brief zainicjowanie modu³u obliczeniowego CRC
 */
void CRC_Configuration(void){
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC,ENABLE);
}

uint32_t RBITProc(uint32_t ul){
#if (__CORTEX_M >= 0x03)
	return(__RBIT(ul));
#else
	int i;
	uint32_t Result=0;
	for (i=0 ; i<32 ; i++){
		if (ul & (1<<(31-i))){
			Result |= (1 << i);
		}
	}
	return Result;
#endif
}

/**
 * @brief Obliczanie CRC-32 tak samo jak dla plików
 *
 * Kod znaleziony pod
 * <a href="https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=%2Fpublic%2FSTe2ecommunities%2Fmcu%2FLists%2Fcortex_mx_stm32%2FCRC%20computation&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=1534">linkiem</a>
 *
 * @par buf: wskaŸnik do bufora znakowego
 * @par size: d³ugoœæ bufora znakowego
 * @return obliczony CRC-32
 */
uint32_t CalculateCRC32(char *buf, int size){
	uint32_t ul;
	int i,j;
	i=size>>2;
	CRC->CR=1;
	while(i--){
		ul=*((uint32_t *)buf);
		buf += 4;
		ul=RBITProc(ul);//reverse the bit order of input data
	    CRC->DR=ul;
	}
	ul=CRC->DR;
	ul=RBITProc(ul);
	i = size & 3;
	while(i--){
		ul ^= (uint32_t)*buf;
		buf++;
		for(j=0; j<8; j++){
			if (ul & 1)
				ul = (ul >> 1) ^ 0xEDB88320;
			else
				ul >>= 1;
		}
	}
	ul^=0xffffffff;//xor with 0xffffffff

	return ul;//now the output is compatible with windows/winzip/winrar
}
