/*
 * mainproc.h
 *
 *  Created on: Jul 5, 2016
 *      Author: mirek
 */

#ifndef MAINPROC_H_
#define MAINPROC_H_

typedef enum MainProcessStates_e{
	None_mp,
	Start_mp,
	PWMpa2Dispatch_mp,
	PWMpa2Show_mp,
	Menu_mp,
	MenuChoice_mp,
	DefaultConfig_mp,
/*	Filter_mp,
	FilterShow_mp,
	PauseRZ13_mp,*/
}MainProcessStates_t;

void MainProcess(void);
void SetPWMpa2(void);

extern volatile uint16_t PWMpa2_period;
extern volatile uint16_t PWMpa2_prescaler;
extern volatile uint16_t PWMpa2_pulse;


#endif /* MAINPROC_H_ */
