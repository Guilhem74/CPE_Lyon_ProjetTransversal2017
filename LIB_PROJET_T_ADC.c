/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_ADC
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
#include "LIB_PROJET_T_ADC.h" 
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void CFG_ADC(void)
{
	 CFG_VREF();
   CFG_ADC0();
}
void CFG_VREF(void)
{
	REF0CN|=0x03; //Activation tension de reference sur le port VREF
}

void CFG_ADC0(void)
{
	AMX0CF&=0xF8; 
	AMX0SL=0x03; //On utilise le port AIN0.3,Utilisation AIN0.3 en unipolaire
	ADC0CN&=0xf3; //Conversion declench?e par une mise a 1 de AD0BUSY
	AD0TM=0; //Conversion declench?e par une mise a 1 de AD0BUSY
	AD0LJST=1;
	AD0EN=1; //Activation ADC0
	AD0INT=0; //ADC0 pret
	
}
/*void SET_AD0BUSY(void)
{
	AD0BUSY=1;
}
char Fin_Conversion(void)
{
	return AD0INT;
}

void CLEAR_ADC_Flag(void)
{
	AD0INT=0;
}
//unsigned char ACQ_ADC(void)
//{
//	AD0BUSY=1; //lancement conversion
// 	while(AD0INT!=1) ;//Attente fin de conversion
//	
//	AD0INT=0;//raz le flag
//	return ADC0H; 
//}*/