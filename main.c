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
// Programme de d�mo pour la mise en oeuvre du la librairie UART0_RingBuffer
// 
// ID_1.7 D�pendances mat�rielles "cible" ----------------------------------------------- 
// Processeur cible: C8051F02x

// ID_1.8 D�pendances mat�rielles "ext�rieures" -----------------------------------------
// Utilisation d'un Bouton Poussoir sur P3.7
// Utilisation d'un oscillateur externe (Quartz)

// ID_1.9 D�pendances de type communications/protocolaires ------------------------------
// Ce code re�oit et envoie des donn�es sur la liaison s�rie asynchrone UART0
// ID_1.10 Fonctionnement du code -------------------------------------------------------
// Le code est destin� � montrer le fonctionnement de la librairie UART0_RingBuffer
// Chaque donn�e re�ue sur la liaison s�rie est stock�e dans un buffer circulaire.
// A chaque appui sur le Bouton Poussoir les donn�es dans le buffer de r�ception sont lues 
// et envoy�es dans le buffer de transmission.

// ID_1.11 Choix technologiques divers --------------------------------------------------


// ID_1.12 Tests r�alis�s ---------------------------------------------------------------
// Validation sur plateforme 8051F020TB avec processeur 8051F020
// Vitesse de transmission: 115200 Baud
// Fr�quence quartz: 22,1184 MHz
//
// ID_1.13 Chaine de compilation --------------------------------------------------------
// KEIL C51 6.03 / KEIL EVAL C51
//
// ID_1.14 Documentation de r�f�rence ---------------------------------------------------
// Datasheet 8051F020/1/2/3  Preliminary Rev. 1.4 12/03 
//
//ID_1.15 Commentaires sur les variables globales et les constantes ---------------------


//*************************************************************************************************
#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <LIB_PROJET_T_Config_Globale.h>
#include <UART0_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif

sbit BP = P3^7;     
sbit PIN= P3^1;




void main(void) {
	 char  c;
	Init_Device();
	   cfg_Clock_UART();
     cfg_UART0_mode1();
     init_Serial_Buffer();                            
     EA = 1;                              /* allow interrupts to happen */
	   serOutstring("mogo 1:0 2:0\r");

while(1) {
    
	
		if ((c=serInchar())!=0){
		if(c=='A')
		{
			PIN=1;
		}
		else
		{
			PIN=0;
		}
		
	}
} /* main */
}