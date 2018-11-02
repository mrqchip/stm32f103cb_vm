
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "procfamily.h"
#include "crc32.h"
#include "usart_diag.h"
#include "timers.h"
#include "pwmtables.h"
#include "nonvolconfig.h"

/**
 * @brief Konfiguracja aplikacji odczytana z flasha i ew. zmieniana przez zapisem
 */
volatile AppConfig_t AppConfig;
#if ISINTERNALCONFIG
volatile InternalConfig_t InternalConfig;
#endif
/**
 * @brief wskaznik do konfiguracji flash
 */
const AppConfig_t *AppNvCfg =(AppConfig_t *)APPCONFIG_ADDRESS;
#if ISINTERNALCONFIG
const InternalConfig_t *InternalNvCfg =(InternalConfig_t *)INTERNALCONFIG_ADDRESS;
#endif

int IsAppConfigCrcCorrect(AppConfig_t *nv){
	return (CalculateCRC32((char *)nv,sizeof(AppConfig_t)-sizeof(uint32_t))==nv->crc);
}

void DefaultAppConfiguration(void){
	AppConfig.OnOff=PWMpa2_OnOffMask;
	AppConfig.PWMpa2_desiredDuty = 50;
	AppConfig.PWMpa2_desiredFrequency = PWMFrequencies/2;
}

void LoadAppConfiguration(void){
	memcpy((void *)&AppConfig,(void *)AppNvCfg,sizeof(AppConfig));
	if (!IsAppConfigCrcCorrect((AppConfig_t *)&AppConfig)|| AppConfig.PWMpa2_desiredFrequency > PWMFrequencies-1){
		MsgToUDiagLn("Konfiguracja poza wartosciami dopuszczalnymi, ustawiono wartosci domyslne");
		DefaultAppConfiguration();
		SaveAppConfiguration();
	}
}

#if ISINTERNALCONFIG
void LoadInternalConfiguration(void){
	memcpy((void *)&InternalConfig,(void *)InternalNvCfg,sizeof(InternalConfig));
	if (CalculateCRC32((char*)&InternalConfig,sizeof(InternalConfig)-4)!=InternalConfig.crc){
		MsgToUDiagLn("Urzadzenie nie zostalo zaktywowane. Przyjeto parametry domyslne");
		InternalConfig.serial_nmbr=0xffffffff;
		InternalConfig.MACaddr[0]=(uint8_t)(ETH_MAC_PRIVATE1>>16);
		InternalConfig.MACaddr[1]=(uint8_t)(ETH_MAC_PRIVATE1>>8);
		InternalConfig.MACaddr[2]=(uint8_t)(ETH_MAC_PRIVATE1>>0);
		InternalConfig.MACaddr[3]=0;
		InternalConfig.MACaddr[4]=0;
		InternalConfig.MACaddr[5]=0;
		SaveInternalConfiguration();
	}
	if (InternalConfig.serial_nmbr==0xffffffff){
		MsgToUDiagLn("Urzadzenie ma nieprawidlowy numer seryjny");
	}
}
#endif

void SaveAppConfiguration(void){
	uint32_t Address, *pFlashData;
	FLASH_Status FLASHStatus;
	AppConfig.crc=CalculateCRC32((char*)&AppConfig,sizeof(AppConfig)-sizeof(uint32_t));
//	DumpMemoryToUDiag((char *)&AppConfig,sizeof(AppConfig));
	FLASH_Unlock();
	FLASHStatus=FLASH_ErasePage(APPCONFIG_ADDRESS);
	if (FLASHStatus ==FLASH_COMPLETE){
		MsgToUDiagLn("Sector erase ok");
		for (Address=APPCONFIG_ADDRESS, pFlashData=(uint32_t *)&AppConfig;
				(Address<(APPCONFIG_ADDRESS+sizeof(AppConfig))) && (FLASHStatus==FLASH_COMPLETE);
				Address+=4, pFlashData++){
			FLASHStatus=FLASH_ProgramWord(Address,*pFlashData);
		}
		if (FLASHStatus==FLASH_COMPLETE){
			MsgToUDiagLn("App configuration saved");
		}
	}
	FLASH_Lock();
//	DumpMemoryToUDiag((char *)NvCfg,sizeof(NonVolConfig_t));
}

#if ISINTERNALCONFIG
void SaveInternalConfiguration(void){
	uint32_t Address, *pFlashData;
	FLASH_Status FLASHStatus;
	InternalConfig.crc=CalculateCRC32((char*)&InternalConfig,sizeof(InternalConfig)-4);
	FLASH_Unlock();
	FLASHStatus=FLASH_ErasePage(INTERNALCONFIG_ADDRESS);
	if (FLASHStatus ==FLASH_COMPLETE){
		MsgToUDiagLn("Sector erase ok");
		for (Address=INTERNALCONFIG_ADDRESS, pFlashData=(uint32_t *)&InternalConfig;
				(Address<(INTERNALCONFIG_ADDRESS+sizeof(InternalConfig))) && (FLASHStatus==FLASH_COMPLETE);
				Address+=4, pFlashData++){
			FLASHStatus=FLASH_ProgramWord(Address,*pFlashData);
		}
		if (FLASHStatus==FLASH_COMPLETE){
			MsgToUDiagLn("Internal configuration saved");
		}
	}
	FLASH_Lock();
}
#endif

