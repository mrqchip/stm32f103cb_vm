/*
 * mainproc.c
 *
 *  Created on: Jul 5, 2016
 *      Author: mirek
 */

#include <stdio.h>
#include <math.h>
#include "procfamily.h"
#include "timers.h"
#include "butterworth.h"
#include "dma.h"
#include "nonvolconfig.h"
#include "io.h"
#include "screw.h"
#include "usart_diag.h"
#include "ascii.h"
#include "pwmtables.h"
#include "mainproc.h"
volatile MainProcessStates_t sMP=Start_mp;
volatile uint16_t PWMpa2_period;
volatile uint16_t PWMpa2_prescaler;
volatile uint16_t PWMpa2_pulse;


/**
 * Ustawia parametry dla PWM na PA2
 */
void SetPWMpa2(void){
	double d;
	TIM2->PSC = PWMtabTim[AppConfig.PWMpa2_desiredFrequency][0];
	TIM2->ARR =  PWMtabTim[AppConfig.PWMpa2_desiredFrequency][1];
	d = AppConfig.PWMpa2_desiredDuty;
	d /= 100.0;
	d *= TIM2->ARR;
	PWMpa2_pulse = round(d);
	TIM2->CCR3 = PWMpa2_pulse;
	if (AppConfig.OnOff & PWMpa2_OnOffMask){
		TIM_Cmd(TIM2, ENABLE);
	}else{
		TIM_Cmd(TIM2, DISABLE);
	}
}

void PWMpa2Show(void){
	volatile double d;
	char buf[64];
/*	d = 72000000.0;
	d /= (TIM2->PSC+1);
	d /= (TIM2->ARR+1);*/
	if (PWMtabFd[AppConfig.PWMpa2_desiredFrequency] >= 100000000){//100kHz
		d = PWMtabFd[AppConfig.PWMpa2_desiredFrequency];
		d /= 1000000.0;
		sprintf(buf,"df=%0.1fkHz;dut=%hu%%;%c   \r",d,AppConfig.PWMpa2_desiredDuty, GetScrew());
	}else if (PWMtabFd[AppConfig.PWMpa2_desiredFrequency] >= 10000000){//10kHz
		d = PWMtabFd[AppConfig.PWMpa2_desiredFrequency];
		d /= 1000000.0;
		sprintf(buf,"df=%0.2fkHz;dut=%hu%%;%c   \r",d,AppConfig.PWMpa2_desiredDuty,GetScrew());
	}else if (PWMtabFd[AppConfig.PWMpa2_desiredFrequency] >= 100000){//100Hz
		d = PWMtabFd[AppConfig.PWMpa2_desiredFrequency];
		d /= 1000.0;
		sprintf(buf,"df=%0.1fHz;dut=%hu%%;%c   \r",d,AppConfig.PWMpa2_desiredDuty,GetScrew());
	}else{
		d = PWMtabFd[AppConfig.PWMpa2_desiredFrequency];
		d /= 1000.0;
		if (PWMtabFd[AppConfig.PWMpa2_desiredFrequency] >= 10000){//10Hz
			sprintf(buf,"df=%0.2fHz;dut=%hu%%;%c   \r",d,AppConfig.PWMpa2_desiredDuty,GetScrew());
		}else{
			sprintf(buf,"df=%0.3fHz;dut=%hu%%;%c   \r",d,AppConfig.PWMpa2_desiredDuty,GetScrew());
		}
	}

	//MsgToUDiag(buf);
/*	d = TIM2->CCR3;
	d /= TIM2->ARR;
	d *= 100;*/
	//sprintf(buf,"duty=%0.1f%%;desduty=%hu %c  \r",d,AppConfig.PWMpa2_desiredDuty, GetScrew());
	MsgToUDiag(buf);
}

void MainProcess(void){
	char buf[64];
	volatile static int SaveConfig;
	volatile double d;
	//volatile uint32_t di;
	switch (sMP){
	case Start_mp:
		if (AppConfig.OnOff & PWMpa2_OnOffMask){
			MsgToUDiagLn("*** generator PWM na PA2 ***");
			MsgToUDiagLn("1 - zwiekszanie czestotliwosci");
			MsgToUDiagLn("2 - zmniejszanie czestotliwosci");
			MsgToUDiagLn("a - zwiekszanie wypelnienia");
			MsgToUDiagLn("z - zmniejszanie wypelnienia");
			sMP = PWMpa2Dispatch_mp;
			break;
		}
		if (DiagComm.fifo_rx->Count>0){
			if (FromUDiagRBuffer()==CTRL_C){
				SaveConfig=0;
				sMP=Menu_mp;
				break;
			}
		}
		if (MainPTimer>0)
			break;
		MainPTimer = SECONDS(1)/10;
		sprintf(buf,"Nie wybrano funkcji%c\r",GetScrew());
		MsgToUDiag(buf);
		break;
	case PWMpa2Dispatch_mp:
		if (MainPTimer==0){
			MainPTimer = SECONDS(1)/10;
			PWMpa2Show();
		}
		if (SaveConfig && SaveRqstTimer == 0){
			SaveAppConfiguration();
			SaveConfig = 0;
		}
		if (DiagComm.fifo_rx->Count==0)
			break;
		switch (FromUDiagRBuffer()){
		case '1':
			if (AppConfig.PWMpa2_desiredFrequency<PWMFrequencies-1){
				AppConfig.PWMpa2_desiredFrequency++;
				SaveConfig = 1;
				SaveRqstTimer = SECONDS(10);
				SetPWMpa2();
			}
			break;
		case '2':
			if (AppConfig.PWMpa2_desiredFrequency>0){
				AppConfig.PWMpa2_desiredFrequency--;
				SaveConfig = 1;
				SaveRqstTimer = SECONDS(10);
				SetPWMpa2();
			}
			break;
		case 'a':
		case 'A':
			if (TIM2->ARR > 100){
				if (AppConfig.PWMpa2_desiredDuty<100){
					AppConfig.PWMpa2_desiredDuty++;
				}else{
					AppConfig.PWMpa2_desiredDuty = 100;
				}
				d = AppConfig.PWMpa2_desiredDuty;
				d /= 100.0;
				d *= TIM2->ARR;
				PWMpa2_pulse = round(d);
				TIM2->CCR3 = PWMpa2_pulse;
			}else{
				if (TIM2->CCR3 < TIM2->ARR){
					TIM2->CCR3++;
				}else{
					TIM2->CCR3 = TIM2->ARR;
				}
				d = TIM2->CCR3;
				d /=TIM2->ARR;
				d *= 100.0;
				AppConfig.PWMpa2_desiredDuty = round(d);
			}
			SaveConfig = 1;
			SaveRqstTimer = SECONDS(10);
			break;
		case 'z':
		case 'Z':
			if (TIM2->ARR > 100){
				if (AppConfig.PWMpa2_desiredDuty>0){
					AppConfig.PWMpa2_desiredDuty--;
				}else{
					AppConfig.PWMpa2_desiredDuty = 0;
				}
				d = AppConfig.PWMpa2_desiredDuty;
				d /= 100.0;
				d *= TIM2->ARR;
				PWMpa2_pulse = round(d);
				TIM2->CCR3 = PWMpa2_pulse;
			}else{
				if (TIM2->CCR3 > 0){
					TIM2->CCR3--;
				}else{
					TIM2->CCR3 = 0;
				}
				d = TIM2->CCR3;
				d /=TIM2->ARR;
				d *= 100.0;
				AppConfig.PWMpa2_desiredDuty = round(d);
			}
			SaveConfig = 1;
			SaveRqstTimer = SECONDS(10);
			break;
		}
		break;
	case PWMpa2Show_mp:
		break;
	case Menu_mp:
		MsgToUDiagLn("\r\n*** Konfiguracja ***\r\n1 - konfiguracja fabryczna");
		MsgToUDiagLn("x - wyjscie");
		sMP = MenuChoice_mp;
		break;
	case MenuChoice_mp:
		if (DiagComm.fifo_rx->Count==0)
			break;
		switch (FromUDiagRBuffer()){
		case '1':
			MsgToUDiagLn("Ustawic konfiguracje fabryczna?(t/n)");
			sMP = DefaultConfig_mp;
			break;
		case '2':
//			sMP = PauseRZ13_mp;
			break;
		case 'x':
		case 'X':
			if (SaveConfig){
				SaveConfig=0;
				SaveAppConfiguration();
			}
			MsgToUDiagLn0();
			sMP = Start_mp;
			break;

		}
		break;
	case DefaultConfig_mp:
		if (DiagComm.fifo_rx->Count==0)
			break;
		switch (FromUDiagRBuffer()){
		case 't':
		case 'T':
			DefaultAppConfiguration();
			SetPWMpa2();
			SaveConfig = 1;
			sMP=Menu_mp;
			break;
		case 'n':
		case 'N':
			sMP=Menu_mp;
			break;
		}
		break;
/*	case FilterShow_mp:
		MsgToUDiag("Filtr: ");
		FilterShow(AppConfig.Averaging);
		MsgToUDiag("              \r");
		sMP=Filter_mp;
		break;*/
/*	case PauseRZ13_mp:
		if (DiagComm.fifo_rx->Count==0)
			break;
		switch (FromUDiagRBuffer()){
		case '1'://100ms
			AppConfig.PauseRZ13 = SECONDS(1)/10;
			SaveConfig = 1;
			sMP = Menu_mp;
			break;
		case '2'://200ms
			AppConfig.PauseRZ13 = SECONDS(1)/5;
			SaveConfig = 1;
			sMP = Menu_mp;
			break;
		case '3'://500ms
			AppConfig.PauseRZ13 = SECONDS(1)/2;
			SaveConfig = 1;
			sMP = Menu_mp;
			break;
		case '4'://1s
			AppConfig.PauseRZ13 = SECONDS(1);
			SaveConfig = 1;
			sMP = Menu_mp;
			break;
		case '5'://2s
			AppConfig.PauseRZ13 = SECONDS(2);
			SaveConfig = 1;
			sMP = Menu_mp;
			break;
		}
		break;*/
	default:
		break;
	}
}
