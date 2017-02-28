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
#ifndef __LIB_BSE_ADC__
#define __LIB_BSE_ADC__
void CFG_ADC(void);
void CFG_VREF(void);

void CFG_ADC0(void);
unsigned char ACQ_ADC(void);
void SET_AD0BUSY(void);
char Fin_Conversion(void);

void CLEAR_ADC_Flag(void);
#endif