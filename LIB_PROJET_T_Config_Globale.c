#ifndef __LIB_BSE_Config_Globale__
#define __LIB_BSE_Config_Globale__
/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Config_Globale
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
#include "LIB_BSE_DAC.h"
#include "LIB_BSE_Config_Globale.h"
#include "LIB_BSE_GPIO.h"  
#include "LIB_BSE_INT_Ext.h"  
#include "LIB_BSE_Timers.h"
#include "LIB_BSE_Reset.h"
#include "LIB_BSE_Clock.h" 
#include "LIB_BSE_UART.h" 
#include "LIB_BSE_ADC.h" 
//------------------------------------------------------------------------------

//*****************************************************************************	 
//Init_Device
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations.
// 
//*****************************************************************************
void Init_Device(void)
{
	CFG_Clock();
	CFG_Reset();
	CFG_GPIO();
	CFG_INT_Ext();
	CFG_Timers();
	CFG_UART();
	CFG_DAC0();
	CFG_ADC();
}
#endif