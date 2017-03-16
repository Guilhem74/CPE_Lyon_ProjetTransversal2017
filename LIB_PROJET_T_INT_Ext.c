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
#include "LIB_PROJET_T_INT_Ext.h"  
//------------------------------------------------------------------------------


//*****************************************************************************	 
//CFG_INT_Ext
//
//	 Cette fonction a pour but de regrouper les fonctions de configurations des interruptions externes.
// 
//*****************************************************************************

void CFG_INT_Ext(void)
{

	Config_INT1();

}

void Config_INT1(void)
{
	IT1=1;//interruption falling edge
	//EX1=1;//Enable external interrupt on /INT1 pin
	//PX1 =  1; // priority int1
	IE1=0;//effacement du flag
}


