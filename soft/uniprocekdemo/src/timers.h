#ifndef _TIMERS_H_
#define _TIMERS_H_

#include <stdint.h>
#define TIMERPRESCALER (2)
#define ONEWIREDIVIDER (66666)
#define ONEWIREPRESCALER (1)
#define SECONDS(s) (s*1000)
enum Timers_e{
	MAINPTIMER,
	SAVERQSTTIMER,
	TIMERS1MS_LOT,
};
#define MainPTimer Timers1ms[MAINPTIMER]
#define SaveRqstTimer Timers1ms[SAVERQSTTIMER]



void RefreshTimers1ms(void);
void TIM2_Configuration(void);
void TIM3_Configuration(void);
void TIM4_Configuration(void);
extern volatile uint32_t Timers1ms[TIMERS1MS_LOT];


#endif
