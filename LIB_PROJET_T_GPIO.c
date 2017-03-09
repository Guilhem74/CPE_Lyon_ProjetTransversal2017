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
	Enable_Crossbar();
	//Output
	/*P2MDOUT|=0x7D;//P2.0 P2.1 P2.3 P2.4 P2.5 P2.6 en push pull
	P3MDOUT|=0xFC;//P3.2 P3.3 P3.4 P3.5 P3.6 P3.7	en push pull
	//INPUT config
	/*Mise a 1 des entrees pour desactiver le LTransistor du push pull*/
	XBR2 |=0x40;

	/*Mise en drain ouvert*/
	P3MDOUT&=0xFC;//P3.1 P3.0 en drain ouvert
	P2MDOUT&=0x7D;//P2.2 P2.7 en drain ouvert
	P1MDOUT&=0xFB;//P1.2 en drain ouvert 
	P0MDOUT&=0xFC;
	P0MDOUT|=0x01;

	//Déclarations
	XBR0|=0x7F;
	XBR1|=0xFF;
	XBR2|=0x6D;
	
	/*End_Config*/
	P1MDOUT|=0x09;//Disable if not sysclock
	P3 |= 0x80;


}

void Enable_Crossbar(void)
{
	XBR2 |=0x40;
}
/*
void Pulse_P20(void)
{
	P2__0=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	P2__0=0;

}
void Pulse_P21(void)
{
	P2__1=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	P2__1=0;

}

void SET_Decl_PES(void)
{
	P3__3=1;
	return;
}
void UNSET_Decl_PES(void)
{
	P3__3=0;
	return;
}
void Set_Erreur(void)
{
	P3__2=0;
	return;
}

char Read_P2_2(void)
{
	return P2__2;
}

void SET_P3_5(void)
{
	P3__5=1;
}
void UNSET_P3_5(void)
{
	P3__5=0;
}*/