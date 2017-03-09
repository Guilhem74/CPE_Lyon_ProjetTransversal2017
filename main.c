//---------------------------------------------------------------------------------------
// ID_1.1    Test_Ring_Buffer.C -----------------------------------------------------
//---------------------------------------------------------------------------------------
// ID_1.2  
//
// ID_1.3 Auteur F.JOLY - CPE Lyon
// ID_1.4 DATE: 08 Mars 2016 
// ID_1.5 Version 1.0 
// 
// ID_1.6 Objectifs ---------------------------------------------------------------------
// Programme de démo pour la mise en oeuvre du la librairie UART0_RingBuffer
// 
// ID_1.7 Dépendances matérielles "cible" ----------------------------------------------- 
// Processeur cible: C8051F02x

// ID_1.8 Dépendances matérielles "extérieures" -----------------------------------------
// Utilisation d'un Bouton Poussoir sur P3.7
// Utilisation d'un oscillateur externe (Quartz)

// ID_1.9 Dépendances de type communications/protocolaires ------------------------------
// Ce code reçoit et envoie des données sur la liaison série asynchrone UART0
// ID_1.10 Fonctionnement du code -------------------------------------------------------
// Le code est destiné à montrer le fonctionnement de la librairie UART0_RingBuffer
// Chaque donnée reçue sur la liaison série est stockée dans un buffer circulaire.
// A chaque appui sur le Bouton Poussoir les données dans le buffer de réception sont lues 
// et envoyées dans le buffer de transmission.

// ID_1.11 Choix technologiques divers --------------------------------------------------


// ID_1.12 Tests réalisés ---------------------------------------------------------------
// Validation sur plateforme 8051F020TB avec processeur 8051F020
// Vitesse de transmission: 115200 Baud
// Fréquence quartz: 22,1184 MHz
//
// ID_1.13 Chaine de compilation --------------------------------------------------------
// KEIL C51 6.03 / KEIL EVAL C51
//
// ID_1.14 Documentation de référence ---------------------------------------------------
// Datasheet 8051F020/1/2/3  Preliminary Rev. 1.4 12/03 
//
//ID_1.15 Commentaires sur les variables globales et les constantes ---------------------


//*************************************************************************************************
                  // SFR declarations
#include <stdio.h>
#include <intrins.h>
//#include <string.h>
#include "LIB_PROJET_T_Config_Globale.h"
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif

sbit BP = P3^7;     
void SerialEvent1();
void SerialEvent0();


void main(void) {
    

     WDTCN     = 0xDE;
			WDTCN     = 0xAD;
		//
	//	
	
//Port_IO_Init();
//Oscillator_Init();
Init_Device();
	cfg_Clock_UART();
		cfg_UARTS_mode1();
		init_Serial_Buffer();   
		init_Serial_Buffer_1();	
		EA = 1;                              /* allow interrupts to happen */
		//serOutstring("\n\rTest_Buffer_Circulaire\n\r");
		//serOutstring_1("mogo 1:40 2:40\r");
		serOutstring("INIT 8051 DONE\r\n");
		
while(1) {
	SerialEvent1();
	 SerialEvent0();
} 
}/* main */

void SerialEvent1()
{
	#define SIZE_BUFF_RECEPT_UART1 5
	static char Reception_Uart1[5];
	static unsigned char Value_Rec1=0;
	char  c;
		int i=0;
	if ((c=serInchar_1())!=0)
	 {
		 if(c=='\n'||c=='\r')
		 {//Message de com ne pas tenir compte pour serializer
		 }
		 else if (c=='>')
		 {//reception terminé, on passe a la suite
			 //TODO ACTION PARSEUR
			  serOutstring(Reception_Uart1);//ici recopie serial
			 Value_Rec1=0;
			  for(i=0;i<SIZE_BUFF_RECEPT_UART1;i++)
				 {
					 Reception_Uart1[i]='\0';
				 }
		 }
		 else
		 {
			 Reception_Uart1[Value_Rec1]=c;
			 Value_Rec1++;
			 if(Value_Rec1>=SIZE_BUFF_RECEPT_UART1)
			 {//protection contre message indé
				 Value_Rec1=0;
				 serOutstring("Message Indé\r\n");
				 for(i=0;i<SIZE_BUFF_RECEPT_UART1;i++)
				 {
					 Reception_Uart1[i]='\0';
				 }
			 }
		 }
	 }
 }
 
void SerialEvent0()
{
	#define SIZE_BUFF_RECEPT_UART0 5
	static char Reception_Uart0[SIZE_BUFF_RECEPT_UART0];
	static unsigned char Value_Rec0=0;
	char  c;
		int i=0;
	if ((c=serInchar())!=0)
	 {
		 if(c=='\r')//Fin de commande putty
		 {//Message de com fin de reception pour PC
			 //TODO ACTION PARSEUR

			 Value_Rec0=0;
			 for(i=0;i<SIZE_BUFF_RECEPT_UART0;i++)
				 {
					 Reception_Uart0[i]='\0';
				 }
		 }
		 else
		 {
			 Reception_Uart0[Value_Rec0]=c;
			 Value_Rec0++;
			  
			 if(Value_Rec0>=SIZE_BUFF_RECEPT_UART0)
			 {//protection contre message indé
				
				 serOutstring("Message Indé\r\n");
				 Value_Rec0=0;
				 for(i=0;i<SIZE_BUFF_RECEPT_UART0;i++)
				 {
					 Reception_Uart0[i]='\0';
				 }
			 }
		 }
	 }
 }

