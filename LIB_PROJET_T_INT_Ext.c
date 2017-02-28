/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_INT_Ext
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
#include "LIB_BSE_INT_Ext.h"  
//------------------------------------------------------------------------------


//*****************************************************************************	 
//CFG_INT_Ext
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des interruptions externes.
// 
//*****************************************************************************

void CFG_INT_Ext(void)
{
	Disable_interrupt();
	Config_INT1();
	Enable_interrupt();
}

void Config_INT1(void)
{
	IE1=0;//effacement du flag
	EX1=1;//Enable external interrupt on /INT1 pin
	XBR1|=0x10;
	IT1=1;//interruption edge
}


void Enable_interrupt(void)
{
	EA=1;
}
void Disable_interrupt(void)
{
	EA=0;
}
void CLEAR_TF2(void)
{
	TF2=0;//Delete flag
}
void CLEAR_IE1(void)
{
	IE1=0;//Delete flag
}
