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
	Config_Timer2();
	Config_Timer1();
}
void Config_Timer2(void)
{
	CKCON&=0xDF;//Divide system clock by 12
	TF2=0;
	EXF2=0;
	EXEN2=0;
	CT2=0;
	RCLK0=0;
	TCLK0=0;
	CPRL2=0;
	RCAP2L=0xff;
	RCAP2H=0xDB;
	TL2=0xff;
	TH2=0xff;
	TR2=1;
	PT2=1;
	ET2=1;
}

void Config_Timer1(void)
{
	CKCON|=(0x10); //Utilisation de l'horloge système
	ET1=0; //On désactive les demandes d'interruption du Timer 1
	TF1=0; //RAZ du flag 
	TMOD&=0x2f; //Timer 1 autoreload, 8bits et independant de /INT0
	TMOD|=0x20; 
	TH1=0xf4; //Baud Rate = 115200 (Système 22.1184MHZ)
	TL1=TH1; //On intitialise le timer 1 pour qu'il commence au bon endroit
	
	TR1=1; //Activation Timer 1
	
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