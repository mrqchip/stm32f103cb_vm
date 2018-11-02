/**
  ******************************************************************************
  * @file    ascii.c
  * @author  Miroslaw Lach
  * @version V.1.0
  * @date    09.02.2012
  * @brief   Procedury przetwarzaj¹ce znaki ASCII
  ******************************************************************************
  * @copyright
  *
  *
  * <h2><center>&copy; COPYRIGHT 2011 Miroslaw Lach</center></h2>
  */

#include <stdio.h>
#include <ctype.h>
#include "ascii.h"

/**
 * @brief ci¹g pary znaków koñca linii
 */
const char NewLineMsg[]="\r\n";

/**
 * @brief konwertuje znaki sterujace ASCII na ich tekstowy odpowiednik, znaki drukowalne przepuszcza bez zmiany
 * @param buf - wskaznik do bufora
 * @param c - znak
 * @return zwraca liczbe znakow zapisanych do buf
 */
int ASCIIConvertUnVisibleChar(char *buf, char c){
	if (isprint((int)c)){
		*buf=c;
		buf++;
		*buf=0;
		return 1;
	}else{
		switch (c){
		case NUL_KEY:
			return sprintf(buf,"<NUL>");
		case SOH_KEY:
			return sprintf(buf,"<SOH>");
		case STX_KEY:
			return sprintf(buf,"<STX>");
		case ETX_KEY:
			return sprintf(buf,"<ETX>");
		case EOT_KEY:
			return sprintf(buf,"<EOT>");
		case ENQ_KEY:
			return sprintf(buf,"<ENQ>");
		case ACK_KEY:
			return sprintf(buf,"<ACK>");
		case BEL_KEY:
			return sprintf(buf,"<BEL>");
		case BS_KEY:
			return sprintf(buf,"<BS>");
		case LF_KEY:
			return sprintf(buf,"<LF>");
		case VT_KEY:
			return sprintf(buf,"<VT>");
		case FF_KEY:
			return sprintf(buf,"<FF>");
		case CR_KEY:
			return sprintf(buf,"<CR>");
		case SO_KEY:
			return sprintf(buf,"<SO>");
		case SI_KEY:
			return sprintf(buf,"<SI>");
		case DLE_KEY:
			return sprintf(buf,"<DLE>");
		case DC1_KEY:
			return sprintf(buf,"<DC1>");
		case DC2_KEY:
			return sprintf(buf,"<DC2>");
		case DC3_KEY:
			return sprintf(buf,"<DC3>");
		case DC4_KEY:
			return sprintf(buf,"<DC4>");
		case NAK_KEY:
			return sprintf(buf,"<NAK>");
		case SYN_KEY:
			return sprintf(buf,"<SYN>");
		case ETB_KEY:
			return sprintf(buf,"<ETB>");
		case CAN_KEY:
			return sprintf(buf,"<CAN>");
		case EM_KEY:
			return sprintf(buf,"<EM>");
		case ESC_KEY:
			return sprintf(buf,"<ESC>");
		case FS_KEY:
			return sprintf(buf,"<FS>");
		case GS_KEY:
			return sprintf(buf,"<GS>");
		case RS_KEY:
			return sprintf(buf,"<RS>");
		case US_KEY:
			return sprintf(buf,"<US>");
		default:
			return sprintf(buf,"<0x%02X>",(int)c);
		}
	}
}

/**
 * @brief dokonuje konwersji znakow niedrukowalnych w buforze,
 * nie sprawdza dlugosci bufora
 * @param bufd - napis wynikowy
 * @param buf - napis podlegajacy konwersji
 * @return dlugosc napisu
 */
int ASCIIConvertUnVisibleCharBuf(char *bufd, char * buf){
	int i,j;
	for (i = 0, j=0 ; buf[i]!=0 ; i++){
		j+=ASCIIConvertUnVisibleChar(bufd+j,buf[i]);
	}
	bufd[j]=0;
	return j;
}

/**
 * @brief dokonuje konwersji znakow niedrukowalnych,
 * ogranicza ilosc znakow przetlumaczonych do wielkosci bufora docelowego
 * @param bufd - napis wynikowy
 * @param buf - napis podlegajacy konwersji
 * @param size - fizyczna dlugosc bufora bufd
 * @return wskaznik do pierwszego znaku nie przetlumaczonego albo NULL,
 * gdy wszystkie znaki zostaly przetlumaczone
 */
char *ASCIInConvertUnVisibleCharBuf(char *bufd, char *buf, int size){
	int i,j,k;
	char tmp[8];
	for (i = 0, j=0 ; buf[i]!=0 ; i++){
		k=ASCIIConvertUnVisibleChar(tmp,buf[i]);
		if (j+k>size-1){
			return buf+i;
		}else{
			j+=sprintf(bufd+j,"%s",tmp);
		}
	}
	bufd[j]=0;
	return NULL;
}
