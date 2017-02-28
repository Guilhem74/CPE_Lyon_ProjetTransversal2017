/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_Clock
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
#include "LIB_BSE_Clock.h"

//*****************************************************************************	 
//CFG_Clock
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations de l'horloge systeme.
// 
//*****************************************************************************
void CFG_Clock(void)
{
	Set_Crystal_22();//Set oscillator extern as system clock on 22.1164MHz
	Enable_Clock_on_pin();//Test
	Disable_int_oscill();
}

//*****************************************************************************	 
//Use_ext_oscill
//
//	 Cette fonction a pour but d'activer l'utilisation de l'oscillateur externe comme horloge système.
// 
//*****************************************************************************
void Use_ext_oscill(void)
{
	OSCICN|=0x08;
}



//*****************************************************************************	 
//Disable_int_oscill
//
//	 Cette fonction a pour but de desactiver l'oscillateur interne.
// 
//*****************************************************************************
void Disable_int_oscill(void)
{
	OSCICN&=~(0x06);
}


////////////////////////////////////////OSC_EXTERNE : OSCXCN

//*****************************************************************************	 
//Set_Crystal_22
//
//	 Cette fonction a pour but de paramétrer l'horloge système sur un quartz de 22.1184 Mhz.
// 
//*****************************************************************************
void Set_Crystal_22(void)
{
	OSCXCN=0x67;
	while(((OSCXCN&0x80)>>7)!=1);//Waiting for crystal oscillator is running and stable
	Use_ext_oscill();
	
}
//*****************************************************************************	 
//Enable_Clock_on_pin
//
//	 Cette fonction de test permet de vérifier la valeur de l'horloge système sur un pin.
// 
//*****************************************************************************
void Enable_Clock_on_pin(void)
{
	XBR2|=0x40;//Enable crossbar to watch sysclock on pin
	XBR1|=0x80;//Use sysclock on first pin available
}


