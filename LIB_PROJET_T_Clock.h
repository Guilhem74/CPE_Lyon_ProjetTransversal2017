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
#ifndef __LIB_PROJET_T_Clock__
#define __LIB_PROJET_T_Clock__
//*****************************************************************************	 
//CFG_Clock
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations de l'horloge systeme.
// 
//*****************************************************************************

void CFG_Clock(void);

//*****************************************************************************	 
//Use_ext_oscill
//
//	 Cette fonction a pour but d'activer l'utilisation de l'oscillateur externe comme horloge système.
// 
//*****************************************************************************
void Use_ext_oscill(void);

//*****************************************************************************	 
//Use_int_oscill
//
//	 Cette fonction a pour but d'activer l'utilisation de l'oscillateur interne comme horloge système.
// 
//*****************************************************************************
void Use_int_oscill(void);

//*****************************************************************************	 
//Enable_int_oscill
//
//	 Cette fonction a pour but d'activer l'oscillateur interne.
// 
//*****************************************************************************
void Enable_int_oscill(void);

//*****************************************************************************	 
//Disable_int_oscill
//
//	 Cette fonction a pour but de desactiver l'oscillateur interne.
// 
//*****************************************************************************
void Disable_int_oscill(void);

//*****************************************************************************	 
//Set_F_int_osc
//
//	 Cette fonction a pour but de choisir la fréquence de l'osc interne.
//  F en Mhz (2,4,8 ou 16)
// 
//*****************************************************************************
void Set_F_int_osc(int f);

////////////////////////////////////////OSC_EXTERNE : OSCXCN

//*****************************************************************************	 
//Set_Crystal_22
//
//	 Cette fonction a pour but de paramétrer l'horloge système sur un quartz de 22.1184 Mhz.
// 
//*****************************************************************************
void Set_Crystal_22(void);

//*****************************************************************************	 
//Enable_Clock_on_pin
//
//	 Cette fonction permet de vérifier la valeur de l'horloge système sur un pin.
// 
//*****************************************************************************
void Enable_Clock_on_pin(void);
//*****************************************************************************	 
//Disable_Clock_on_pin
//
//	 Cette fonction permet de désactiver l'observation de l'horloge sur un GPIO.
// 
//*****************************************************************************
void Disable_Clock_on_pin(void);
#endif
