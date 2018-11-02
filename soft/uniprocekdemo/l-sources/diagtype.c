/*
 * diagtype.c
 *
 *  Created on: Jun 4, 2012
 *      Author: mirek
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ascii.h"
#include "fifobuf.h"
#include "serialcomm.h"
#include "usart_diag.h"
#include "diagtype.h"
const char Res_Msg[]="\r\nResult=";
const char Asterisks_Msg[]="*******";
/**
 * @brief wskaznik do odbiorczej kolejki fifo portu usart
 */
const fifobuf_t *RBuf=&sUDiagRBuf;
/**
 * @brief wskaznik do procedury odbioru znaku z odbiorczej kolejki fifo portu usart
 */
const FromUsart fu=FromUDiagRBuffer;
/**
 * @brief wskaznik do procedury zapisu znaku do nadawczej kolejki fifo portu usart
 */
const ToUsart tu=ToUDiagTBuffer;
/**
 * @brief wskaznik do procedury wysy³ania napisu do kolejki nadawczej fifo portu usart
 */
const MsgToUsart msgtu=MsgToUDiag;
const MsgToUsart msgtuln=MsgToUDiagLn;

UDiagTypeProcessStates_t psUDT=UDT_None;
UDiagTypeCharset_t udtc;
char UDiagEditLength;
char UDiagTypeIsPassword;
uint8_t UDiagTypeMACresult[6];
UDiagResult_t UDiagResult;

/**
 *
 * @brief  Proces wprowadzania danych z klawiatury.
 *
 *  Jest to prymitywny edytor wprowadzania danych na terminalu, nie umozliwia kasowania ostatnio
 *  wprowadzonych znakow, za to mozna wyjsc bez uzyskania wyniku
  * @param  UDiagCharset: zestaw znakow, do wyboru:
  *     @arg   Decimal_UDTC: znaki cyfr dziesietnych
  *     @arg   Hex_UDTC: znaki cyfr hex
  *     @arg   Printable_UDTC: wszystkie znaki drukowalne
  *     @arg   PhoneNumber_UDTC: znaki numeru telefonu: plus oraz cyfry
  *     @arg   Float_UDTC: liczba zmiennoprzecinkowa: cyfry, plus, minus, kropka
  * @param  UDiagTypeIsPassword: zmienna bitowa decydujaca czy wprowadzane dane sa haslem
  * @param  UDiagEditLength: dlugosc pola do wprowadzania znakow
  * @param  psUDT: zmienna stanu procesu
  *     @arg   	None_UDT: stan wylaczenia procesu
  *     @arg   	Read_UDT: odczyt znakow i ich interpretacja zaleznie od UDiagCharset
  *     @arg   	EvalResult_UDT: obliczenie liczb calkowitych
  *     @arg   	Break_UDT: stan wycofania sie z wprowadzania
  *     @arg   	ReadHDigit_UDT: odczyt liczby hex
  *     @arg   	EvalHResult_UDT: obliczenie wyniku liczby hex
  *     @arg   	EvalPrintResult_UDT: wyslanie wyniku na terminal
  * @retval UDiagTypeResult[UDIAGTYPERESULT]: bufor ze znakami tekstowymi
  * @retval UDiagIntTypeResult: bufor z wynikiem calkowitym
  */
void UDiagTypeProcess(void){
	char c;
	static char Result[64];
	static int i;
#if UDIAGTYPE_IP
	char *cp;
	static int subipidx;
	static int ipidx;
#endif
	float f;
	switch (psUDT){
	case UDT_None:
		i=0;
		break;
	case UDT_Start:
		i=0;
#if UDIAGTYPE_IP
		ipidx=0;
		subipidx=0;
#endif
		psUDT=UDT_Read;
		break;
	case UDT_Read:
		if (RBuf->Count==0)
			break;
		c=fu();
		switch (udtc){
		case UDTC_None:
			break;
#if UDIAGTYPE_DECIMAL
		case UDTC_Decimal:
			if (!(isdigit((int)c) || c==CTRL_M || c==ESC_KEY))
				break;
			if (c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength)
				break;
			Result[i]=c;
			if (UDiagTypeIsPassword){
				tu('*');
			}else{
				tu(c);
			}
			i++;
			break;
#endif
#if UDIAGTYPE_HEX
		case UDTC_Hex:
			if (!(isxdigit((int)c) || c==CTRL_M || c==ESC_KEY))
				break;
			if (c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalHResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength)
				break;
			c=toupper((int)c);
			Result[i]=c;
			if (UDiagTypeIsPassword){
				tu('*');
			}else{
				tu(c);
			}
			i++;
			break;
#endif
#if UDIAGTYPE_PRINTABLE
		case UDTC_Printable:
			if (!(isprint((int)c) || c==CTRL_M || c==ESC_KEY))
				break;
			if(c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalPrintResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength){
				break;
			}
			Result[i]=c;
			Result[i+1]=0;
			if (UDiagTypeIsPassword){
				tu('*');
			}else{
				tu(c);
			}
			i++;
			break;
#endif
#if UDIAGTYPE_PHONENUMBER
		case UDTC_PhoneNumber:
			if (!(isdigit((int)c) || c==CTRL_M || c==ESC_KEY || c=='+'))
				break;
			if (c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalPrintResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength)
				break;
			Result[i]=c;
			if (UDiagTypeIsPassword){
				tu('*');
			}else{
				tu(c);
			}
			i++;
			break;
#endif
#if UDIAGTYPE_FLOAT
		case UDTC_Float:
			if (!(isdigit((int)c) || c=='+' || c=='-' || c=='.' || c==ESC_KEY || c==CTRL_M))
				break;
			if (c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalFloatResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength)
				break;
			if ((c=='+' || c=='-') && i!=0)
				break;
			Result[i]=c;
			tu(c);
			i++;
			if (c=='.'){
				udtc=UDTC_FloatFract;
				break;
			}
			break;
		case UDTC_FloatFract:
			if (!(isdigit((int)c) || c==ESC_KEY || c==CTRL_M))
				break;
			if (c==0x0d || c==0x0a){
				Result[i]=0;
				psUDT=UDT_EvalFloatResult;
				break;
			}
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (i>=UDiagEditLength)
				break;
			Result[i]=c;
			tu(c);
			i++;
			break;
#endif
#if UDIAGTYPE_MAC
		case UDTC_MACaddress:
			if (!(isxdigit((int)c) || c==ESC_KEY))
				break;
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			Result[i]=c;
			tu(c);
			if (i==1 || i==4 || i==7 || i==10 || i==13){
				Result[++i]=0;
				tu('-');
			}
			i++;
			if (i>=17){
				Result[i]=0;
				psUDT=UDT_EvalMACResult;
			}
			break;
#endif
#if UDIAGTYPE_IP
		case UDTC_IPaddress:
			if (!(isdigit((int)c) || c==ESC_KEY || c=='.' || c==CTRL_M))
				break;
			if (c==ESC_KEY){
				psUDT=UDT_Break;
				break;
			}
			if (c != CTRL_M){
				if (c!='.'){
					Result[i]=c;
					tu(c);
					i++;
					subipidx++;
				}else{
					if (subipidx==0){
						Result[i++]='0';
						tu('0');
					}
					subipidx=3;
				}
				if (subipidx>=3){
					subipidx=0;
					Result[i++]=0;
					if (ipidx<=3)
					tu('.');
					ipidx++;
				}
			}
			if ((ipidx>=4) || (c==CTRL_M && ipidx==3)){
				Result[i]=0;
				psUDT=UDT_EvalIPResult;
			}
			break;
#endif
		default:
			break;
		}
		break;
	case UDT_EvalResult:
		sscanf(Result,"%ld",&UDiagResult.IntResult);
		psUDT=UDT_None;
		break;
	case UDT_Break:
		break;
#if UDIAGTYPE_HEX
	case UDT_ReadHDigit:
		if (RBuf->Count==0)
			break;
		c=fu();
		if (!(isxdigit((int)c) || c==CTRL_M || c==ESC_KEY))
			break;
		if (c==CTRL_M){
			Result[i]=0;
			psUDT=UDT_EvalHResult;
			break;
		}
		if (c==ESC_KEY){
			psUDT=UDT_Break;
		}
		if (i>4)
			break;
		Result[i]=toupper((int)c);
		if (UDiagTypeIsPassword){
			tu('*');
		}else{
			tu(c);
		}
		i++;
		break;
	case UDT_EvalHResult:
		sscanf(Result,"%lx",&UDiagResult.IntResult);
		psUDT=UDT_None;
		break;
#endif
	case UDT_EvalPrintResult:
		memcpy(UDiagResult.PrResult,Result,sizeof(UDiagResult.PrResult));
		psUDT=UDT_None;
		break;
#if UDIAGTYPE_FLOAT
	case UDT_EvalFloatResult:
		sscanf(Result,"%f",&f);
		UDiagResult.DblResult=f;
		psUDT=UDT_None;
		break;
#endif
#if UDIAGTYPE_MAC
	case UDT_EvalMACResult:
		UDiagResult.PrResult[0]=(uint8_t)strtol(Result,(char **)NULL,16);
		UDiagResult.PrResult[1]=(uint8_t)strtol(Result+3,(char **)NULL,16);
		UDiagResult.PrResult[2]=(uint8_t)strtol(Result+6,(char **)NULL,16);
		UDiagResult.PrResult[3]=(uint8_t)strtol(Result+9,(char **)NULL,16);
		UDiagResult.PrResult[4]=(uint8_t)strtol(Result+12,(char **)NULL,16);
		UDiagResult.PrResult[5]=(uint8_t)strtol(Result+15,(char **)NULL,16);
		psUDT=UDT_None;
		break;
#endif
#if UDIAGTYPE_IP
	case UDT_EvalIPResult:
		UDiagResult.PrResult[0]=(uint8_t)strtol(Result,&cp,10);
		UDiagResult.PrResult[1]=(uint8_t)strtol(cp+1,&cp,10);
		UDiagResult.PrResult[2]=(uint8_t)strtol(cp+1,&cp,10);
		UDiagResult.PrResult[3]=(uint8_t)strtol(cp+1,&cp,10);
		psUDT=UDT_None;
		break;
#endif
	default:
		break;
	}
}

