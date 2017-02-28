/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_UART
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
#include "LIB_BSE_UART.h"
#include <intrins.h>


void CFG_UART(void)
{
	CFG_UART0_CLOCK();
	CFG_UART0();
	/*1
Asynchronous
Timer 1 or 2 Overflow
8 (LSB first)
1 Start, 1 Stop*/
}

void CFG_UART0_CLOCK(void)
{
	RCLK0=0; //UART0 est basé sur le Timer1 
	TCLK0=0; 
	PCON|=0x80; //On ne souhaite pas diviser le baudrate par 2
}

void CFG_UART0(void)
{
	PCON&=0xbf; //Acces au mode de l'uart
	SCON0|=0x60; //On active l'UART0
	SCON0&=0x6C; //RAZ du flag de réception
	SCON0|=0x70; //On active l'UART0
	TI0=1;  //Mise a 1 du flag de transmission
}

//char Putchar(char c, unsigned char csg_tempo)
//{
//		int i=0;
//		while(csg_tempo>=0)
//		{
//			if(TI0==0) //Prêt à transmettre ?
//			{
//					NOP2048();
//					NOP128();
//					NOP32();
//					NOP4();

//				csg_tempo=csg_tempo-1; //On decrémente csg_tempo
//			}
//			else
//			{
//				SBUF0=c; //Envoi du caractère dans le registre de données de l'UART0
//				TI0=0; //RAZ du flag d'émission
//				return c;
//				
//			}
//		}
//	return 0;
//}


//char Getchar(void)
//{
//	char Donnees;
//	if(RI0==0)
//		return 0;
//	Donnees=SBUF0;//on recupere les données du buffer
//	RI0=0;
//	return Donnees;
//}

//char Send_String(char* char_ptr)
//{
//	char Nbr_caractere_envoye=0;
//	unsigned char time_out=100;
//	char Code_retour;
//	while(*char_ptr != '\0')
//	{
//		Code_retour=Putchar(*char_ptr,time_out);
//		if(Code_retour==0)
//			return 0;
//		if(Code_retour!=*char_ptr)
//			return 0;
//		Nbr_caractere_envoye=Nbr_caractere_envoye+1;
//		char_ptr=char_ptr+1;
//	}
//	return Nbr_caractere_envoye;	
//}


//void test_uart(void)
//{

//	char carac = Getchar();
//	if(carac!=0)
//	 Putchar(carac,100);

//}