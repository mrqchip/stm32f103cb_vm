#ifndef _NONVOLCONFIG_H_
#define _NONVOLCONFIG_H_


#define ISINTERNALCONFIG 0
#define SENSVALS 64
#define PTEMPVALS 64
#define THTEMPVALS 64
#define ZEROLEVEL 200
#define ZEROLEVELSIGMA 1

/**
 * @brief adres sektora konfiguracyjnego pamieci flash mikrokontrolera
 */
#define APPCONFIG_ADDRESS (FLASH_BASE+0x1fc00)


typedef enum Averaging_e{
	no_avr,
	butter5Hz_avr,
	butter2Hz_avr,
	butter1Hz_avr,
	butter0Hz75_avr,
	butter0Hz5_avr,
	butter0Hz3_avr,
	butter0Hz2_avr,
	butter0Hz1_avr,
	avrLot_avr
}Averaging_t;

#define PWMpa2_OnOffMask 0x00000001
/**
 * @brief Konfiguracja aplikacji zapisana w ostatnim sektorze flasha mikrokontrolera
 */
struct AppConfig_s{
	uint32_t OnOff;
	uint16_t PWMpa2_desiredDuty;// ¿¹dana wartosc w procentach wypelnienia
	uint32_t   PWMpa2_desiredFrequency;// indeks ¿¹danej czêstotliwoœci
	uint32_t crc;
}__attribute__ ((__packed__));

typedef struct AppConfig_s AppConfig_t;

/**
 * @brief Konfiguracja wewnetrzna zapisana w przedostatnim sektorze flasha mikrokontrolera
 */
/*typedef struct InternalConfig_s{
	uint32_t serial_nmbr;
	uint8_t MACaddr[6];
	uint32_t crc;
}InternalConfig_t;*/

extern const AppConfig_t *AppNvCfg;
#if ISINTERNALCONFIG
extern const InternalConfig_t *InternalNvCfg;
#endif

/**
 * @brief Konfiguracja aplikacji odczytana z flasha i ew. zmieniana przez zapisem
 */
extern volatile AppConfig_t AppConfig;
#if ISINTERNALCONFIG
extern volatile InternalConfig_t InternalConfig;
#endif


void SaveAppConfiguration(void);
void LoadAppConfiguration(void);
int IsAppConfigCrcCorrect(AppConfig_t *nv);
void DefaultAppConfiguration(void);
#if ISINTERNALCONFIG
void SaveInternalConfiguration(void);
void LoadInternalConfiguration(void);
#endif

#endif
