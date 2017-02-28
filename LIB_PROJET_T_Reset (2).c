/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Reset
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
#include "LIB_BSE_Reset.h"

//*****************************************************************************	 
//CFG_Reset
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des resets.
// 
//*****************************************************************************

void CFG_Reset(void)
{
	Disable_reset_source();
	Disable_Watchdog();
}
//*****************************************************************************	 
//Disable_Watchdog
//
//	 Cette fonction a pour but de désactiver le watchdog.
// 
//*****************************************************************************

void Disable_Watchdog(void)
{
	EA=0;//Desactivation des interruptions 
	WDTCN=0xDE;
	WDTCN=0xAD;
	EA=1;//Reactivation des interruptions
}

//*****************************************************************************	 
//Disable_reset_source
//
//	 Cette fonction a pour but de desactiver la plupart des sources de reset
// Desactive le reset par : CNVSTR/Comparator0
// Par sécurité on met a 0 les bits de SWRSF et PORSF
//*****************************************************************************
void Disable_reset_source(void)
{
	Clean_Reset();
	Disable_reset_CNVSTR();
	Disable_reset_Comp0();
}


//*****************************************************************************	 
//Disable_reset_CNVSTR
//
//	 Cette fonction a pour but de desactivet le reset par CNVSTR
// Par sécurité on met a 0 les bits de SWRSF et PORSF
// 
//*****************************************************************************

void Disable_reset_CNVSTR(void)
{
	Clean_Reset();
	RSTSRC&=0xBF;
}

//*****************************************************************************	 
//Disable_reset_Comp0
//
//	 Cette fonction a pour but de desactiver le reset par Comparator0
//   Par sécurité on met a 0 les bits de SWRSF et PORSF
// 
//*****************************************************************************

void Disable_reset_Comp0(void)
{
	Clean_Reset();
	RSTSRC&=0xDF;
}
//*****************************************************************************	 
//Clean_Reset
//
//	 Cette fonction a pour but de mettre a zero les bits de SWRSF et PORSF
// 
//*****************************************************************************

void Clean_Reset(void)
{
	RSTSRC&=0XED;//Force SWRSF et PORSF a 0
}