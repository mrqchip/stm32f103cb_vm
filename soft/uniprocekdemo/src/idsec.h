/*
 * idsec.h
 *
 *  Created on: Oct 26, 2011
 *      Author: mirek
 */

#ifndef IDSEC_H_
#define IDSEC_H_
#define  SECKEY0 0x73
#define  SECKEY1 0xa4
#define  SECKEY2 139
#define  SECKEY3 36
#define  SECKEY4 53
#define  SECKEY5 244
#define  SECKEY6 202
#define  SECKEY7 194
#define  SECKEY8 90
#define  SECKEY9 66
#define  SECKEY10 9
#define  SECKEY11 186
#define  SECKEY12 158
#define  SECKEY13 173
#define  SECKEY14 243
#define  SECKEY15 129
#define  SECKEY16 205
#define  SECKEY17 42
#define  SECKEY18 6
#define  SECKEY19 179
#define  SECKEY20 74
#define  SECKEY21 96
#define  SECKEY22 178
#define  SECKEY23 73
#define  SECKEY24 191
#define  SECKEY25 48
#define  SECKEY26 23
#define  SECKEY27 0x0f
#define  SECKEY28 0xb7
#define  SECKEY29 0x05
#define  SECKEY30 0x55
#define  SECKEY31 0xdb
#define  SECKEY32 0x3e
#define  SECKEY33 0x01
#define  SECKEY34 0x95
#define  SECKEY35 0x77
#define  SECKEY36 0xc1
#define  SECKEY37 0xaf
#define  SECKEY38 0x3f
#define  SECKEY39 0x41
#define  SECKEY40 0xc9
#define  SECKEY41 0xcc
#define  SECKEY42 0xf8
#define  SECKEY43 251
#define  SECKEY44 90
#define  SECKEY45 65
#define  SECKEY46 110
#define  SECKEY47 246
#define  SECKEY48 125
#define  SECKEY49 0
#define  SECKEY50 229
#define  SECKEY51 159
#define  SECKEY52 174
#define  SECKEY53 203
#define  SECKEY54 63
#define  SECKEY55 99
#define  SECKEY56 142
#define  SECKEY57 174
#define  SECKEY58 148
#define  SECKEY59 46
#define  SECKEY60 209
#define  SECKEY61 74
#define  SECKEY62 92
#define  SECKEY63 3
#define  SECKEY64 91
#define  SECKEY65 15
#define  SECKEY66 78

typedef struct IdSoft_s{
	unsigned char SoftTimeStamp[16];
	unsigned char SoftBuild[8];
	unsigned char IDSoft[16];
}IdSoft_t;

extern  __attribute__((section(".idsec"))) const IdSoft_t IDSoft;

void ReadProcessorID(unsigned long int *id);

#endif /* IDSEC_H_ */
