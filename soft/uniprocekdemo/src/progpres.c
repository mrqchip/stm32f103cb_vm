#include <stdio.h>
#include <stdlib.h>
#include "procfamily.h"
#include "usart_diag.h"
#include "idsec.h"
#include "programid.h"
#include "io.h"
//#include "main_process.h"
#include "progpres.h"

#define SIZEOFCONFIG 0
void ProgramPresentation(void){
	char buf[64];
	IdSoft_t Id;
	MsgToUDiagLn0();
	MsgToUDiagLn("Program demonstracyjny plytki UniProcek");
	MsgToUDiagLn("(C)M.Lach MRQ (www.m/j/lach.com)");
	MsgToUDiagLn("Hardware UniProcek1");
	if (DecryptProgramID(&Id)){
		sprintf(buf,"Software uniprocekdemo.cproject v.1.%s, ",Id.SoftTimeStamp);
		MsgToUDiag(buf);
		sprintf(buf,"build %d",atoi((char *)Id.SoftBuild));
		MsgToUDiagLn(buf);
	}
#ifdef DEBUG
	MsgToUDiagLn("!! Wersja deweloperska !!");
#endif
	//MsgToUDiagLn("Ctrl-C - konfiguracja");
#if SIZEOFCONFIG
	sprintf(buf,"sizeof(AppConfig)=%d",sizeof(AppConfig));
	MsgToUDiagLn(buf);
#endif
	MsgToUDiagLn0();
}

