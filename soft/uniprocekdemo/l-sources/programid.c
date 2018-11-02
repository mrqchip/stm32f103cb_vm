#include "idsec.h"

char IDSoftKeys[34]={
		SECKEY0,
		SECKEY1,
		SECKEY2,
		SECKEY3,
		SECKEY4,
		SECKEY5,
		SECKEY6,
		SECKEY7,
		SECKEY8,
		SECKEY9,
		SECKEY10,
		SECKEY11,
		SECKEY12,
		SECKEY13,
		SECKEY14,
		SECKEY15,
		SECKEY16,
		SECKEY17,
		SECKEY18,
		SECKEY19,
		SECKEY20,
		SECKEY21,
		SECKEY22,
		SECKEY23,
		SECKEY24,
		SECKEY25,
		SECKEY26,
		SECKEY27,
		SECKEY28,
		SECKEY29,
		SECKEY30,
		SECKEY31,
		SECKEY32,
		SECKEY33,
};

/**
 * @brief odszyfrowanie danych identyfikacyjnych programu
 * @param Id wskaünik do struktury IdSoft_t
 * @return 1 - gdy ID programu sie zgadza
 */
int DecryptProgramID(IdSoft_t *Id){
	int i;
	for (i=0 ; i<12 ; i++){
		Id->SoftTimeStamp[i]=IDSoft.SoftTimeStamp[i] ^ IDSoftKeys[i];
	}
	Id->SoftTimeStamp[i]=0;
	for (i=0 ; i<6 ; i++){
		Id->SoftBuild[i]=IDSoft.SoftBuild[i] ^ IDSoftKeys[i+12];
	}
	Id->SoftBuild[i]=0;
	for (i=0 ; i<16 ; i++){
		if (IDSoft.IDSoft[i]!=IDSoftKeys[i+18]){
			return 0;
		}
	}
	return 1;
}

