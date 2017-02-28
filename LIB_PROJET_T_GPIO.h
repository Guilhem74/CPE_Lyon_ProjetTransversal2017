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
#ifndef __LIB_BSE_GPIO__
#define __LIB_BSE_GPIO__

//*****************************************************************************	 
//CFG_GPIO
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des GPIOS.
// 
//*****************************************************************************
void CFG_GPIO(void);

void Set_GPIO(void);

void Enable_Crossbar(void);
void Pulse_P20(void);
void Pulse_P21(void);
void SET_Decl_PES(void);
void UNSET_Decl_PES(void);
void Set_Erreur(void);
char Read_P2_2(void);
void SET_P3_5(void);
void UNSET_P3_5(void);
#endif