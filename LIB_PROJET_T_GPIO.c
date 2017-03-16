/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_GPIO
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/
//-------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
                  // SFR declarations
#include "LIB_PROJET_T_GPIO.h"
#include <c8051f020.h> 
#include "Declaration_GPIO.h" 
#include <intrins.h>

//------------------------------------------------------------------------------

//*****************************************************************************	 
//CFG_GPIO
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des GPIOS.
// 
//*****************************************************************************
void CFG_GPIO(void)
{
	Set_GPIO();
	
}
void Set_GPIO(void)
{
   XBR0=0x07;
	 XBR1=0x94;
	XBR2=0x44;
	P0MDOUT|=0x01;
	P0MDOUT&=0xFD;
	P0|=0x40;
	P1MDOUT|=0x11;
	P1MDOUT&=0xFD;
	P1|=0x70;
	P3MDOUT|=0xD0;
	P74OUT |= 0x30;
	//P0MDOUT
}


