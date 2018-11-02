/*
 * diagtype.h
 *
 *  Created on: Jun 4, 2012
 *      Author: mirek
 */

#ifndef DIAGTYPE_H_
#define DIAGTYPE_H_

#define UDIAGTYPERESULT 64
#define UDIAGTYPE_DECIMAL 1
#define UDIAGTYPE_HEX 1
#define UDIAGTYPE_PRINTABLE 0
#define UDIAGTYPE_PHONENUMBER 0
#define UDIAGTYPE_FLOAT 1
#define UDIAGTYPE_MAC 0
#define UDIAGTYPE_IP 0

typedef enum{
	UDT_None,
	UDT_Start,
	UDT_Read,
	UDT_EvalResult,
	UDT_Break,
#if UDIAGTYPE_HEX
	UDT_ReadHDigit,
	UDT_EvalHResult,
#endif
	UDT_EvalPrintResult,
#if UDIAGTYPE_FLOAT
	UDT_EvalFloatResult,
#endif
#if UDIAGTYPE_MAC
	UDT_EvalMACResult,
#endif
#if UDIAGTYPE_IP
	UDT_EvalIPResult,
#endif
	UDT_LastItem
}UDiagTypeProcessStates_t;

typedef enum {
  UDTC_None,
#if UDIAGTYPE_DECIMAL
  UDTC_Decimal,
#endif
#if UDIAGTYPE_HEX
  UDTC_Hex,
#endif
#if UDIAGTYPE_PRINTABLE
  UDTC_Printable,
#endif
#if UDIAGTYPE_PHONENUMBER
  UDTC_PhoneNumber,
#endif
#if UDIAGTYPE_FLOAT
  UDTC_Float,
  UDTC_FloatFract,
#endif
#if UDIAGTYPE_MAC
  UDTC_MACaddress,
#endif
#if UDIAGTYPE_IP
  UDTC_IPaddress,
#endif
  UDTC_LastItem
} UDiagTypeCharset_t;

typedef union {
	char PrResult[UDIAGTYPERESULT];
	long int IntResult;
	double DblResult;
}UDiagResult_t;

typedef char (*FromUsart)(void);
typedef void (*ToUsart)(char c);
typedef void (*MsgToUsart)(char *buf);

void UDiagTypeProcess(void);

extern UDiagTypeProcessStates_t psUDT;
extern UDiagTypeCharset_t udtc;
extern char UDiagEditLength;
extern char UDiagTypeIsPassword;
extern uint8_t UDiagTypeMACresult[6];
//extern long int UDiagIntTypeResult;
//extern char UDiagTypeResult[UDIAGTYPERESULT];
extern UDiagResult_t UDiagResult;
#endif /* DIAGTYPE_H_ */
