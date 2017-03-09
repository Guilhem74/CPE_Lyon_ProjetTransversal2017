/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Timers
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include "LIB_PROJET_T_Timers.h"

unsigned char RTC_Centieme=0;
unsigned char RTC_Secondes=0;
unsigned char RTC_Minutes=0;
unsigned char RTC_Heures=0;
//*****************************************************************************	 
//CFG_Global
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des Timers.
// 
//*****************************************************************************

void CFG_Timers(void)
{

}

/*
void Horloge_RTC(void)
{

	static char t=0;
	if(t==1)
	{//10ms
		RTC_Centieme++;;//+ 10ms
		t=0;
	}
	else
	{//5ms
		t=1;
	}
	if(RTC_Centieme==100)//Quand on est a 100*10 ms -> 1s
	{
		RTC_Secondes=RTC_Secondes+1;
		RTC_Centieme=0;
	}
	if(RTC_Secondes==60)
	{
		RTC_Minutes=RTC_Minutes+1;
		RTC_Secondes=0;
	}
	if(RTC_Minutes==60)
	{
		RTC_Heures=RTC_Heures+1;
		RTC_Minutes=0;
	}
	if(RTC_Heures==24)
	{
		clear_RTC();
	}
}
void clear_RTC(void)
{
	RTC_Centieme=0;
	RTC_Secondes=0;
	RTC_Minutes=0;
	RTC_Heures=0;
}
unsigned long int Conversion_horloge_en_centiemes()
{
		return RTC_Centieme+RTC_Secondes*100+RTC_Minutes*6000+RTC_Heures*360000;
}*/