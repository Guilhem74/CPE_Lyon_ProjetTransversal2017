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

#ifndef __LIB_PROJET_T_Reset__
#define __LIB_PROJET_T_Reset__
//*****************************************************************************	 
//CFG_Reset
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des resets.
// 
//*****************************************************************************
void CFG_RESET(void);

//*****************************************************************************	 
//Disable_Watchdog
//
//	 Cette fonction a pour but de désactiver le watchdog.
// 
//*****************************************************************************

void Disable_Watchdog(void);

//*****************************************************************************	 
//Enable_Watchdog_max
//
//	 Cette fonction a pour but de d'activer le watchdog et le configurer pour qu'il ne s'active que dans un temps maximum.
// 
//*****************************************************************************
void Enable_Watchdog_max(void);

//*****************************************************************************	 
//Disable_reset_source
//
//	 Cette fonction a pour but de desactiver la plupart des sources de reset
// Desactive le reset par : CNVSTR/Comparator0
// Par sécurité on met a 0 les bits de SWRSF et PORSF
//*****************************************************************************
void Disable_reset_source(void);

//*****************************************************************************	 
//Enable_reset_CNVSTR
//
//	 Cette fonction a pour but d'activer le reset par CNVSTR
// Par sécurité on met a 0 les bits de SWRSF et PORSF
// 
//*****************************************************************************
void Enable_reset_CNVSTR(void);
void Disable_reset_CNVSTR(void);
//*****************************************************************************	 
//Enable_reset_Comp0
//
//	 Cette fonction a pour but d'activer le reset par Comparator0
//   Par sécurité on met a 0 les bits de SWRSF et PORSF
// 
//*****************************************************************************
void Enable_reset_Comp0(void);
void Disable_reset_Comp0(void);

//*****************************************************************************	 
//Clean_Reset
//
//	 Cette fonction a pour but de mettre a zero les bits de SWRSF et PORSF
// 
//*****************************************************************************
void Clean_Reset(void);
#endif
