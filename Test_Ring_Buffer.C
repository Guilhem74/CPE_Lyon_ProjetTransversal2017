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
#include <c8051f020.h>                    // SFR declarations
#include <stdio.h>
#include <intrins.h>
#include <string.h>
#include <math.h>
#include <UART0_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif
#include "define.h"
sbit BP = P3^7;     
unsigned int Indice_Reception=0;
char Reception[6]="";
unsigned int busy=0;
	int X_POS=0,Y_POS=0,O_POS=0;
	int X_DES=0,Y_DES=0,O_DES=0,O_FINAL=0;

// ****************************************************************************
//
//*****************************************************************************
void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;
}
void Port_IO_Init()
{
   P0MDOUT   =  0x01;
	 XBR0      = 0x04;
   XBR2      = 0x40;
	 P3        |= 0x80;
}
void UARTEvent()
{
	char c;
	int i=0;
		if ((c=serInchar())!=CARACT_BUFFER_VIDE)//Si on a recu un caractère UART 0 TODO Changement pour uart 1
		{
			if(Indice_Reception>=5)
			{//Message de taille trop grande, on supprime
				for(i=0;i<5;i++)
				{
					Reception[i]='\0';
				}
			}
			else
			{//On doit analyser le caractere recue
				if(c=='\n')//Fin de chaine recue
				{
					//To DO fonctionne de parsage + flush du tableau reception
				}
				else
				{//On stocke le caractère
					Reception[Indice_Reception]=c;
					Indice_Reception++;
				}
			}
		}
}
int Analyse_Deplacement()
{
	if(busy==1)//Si le robot est occupé on analyse pas les prochaines demandes
	{
		return 0;
//		serOutstring("Nothing\n");
	}
	//Le robot n'est pas occupé, il doit donc se deplacer
	if(X_POS!=X_DES || Y_POS!=Y_DES )
	{//Mauvaise position XY, on calcule donc O optimal et on s'y place
		O_DES=90-atan2(Y_DES-Y_POS,X_DES-X_POS)* 180 / PI;
	}
	else
	{//Position XY bonne, on se met donc a l'angle voulu
		O_DES=O_FINAL;
	}
		if(O_POS!=O_DES)
		{//On se met a l'angle voulu si on ne l'est pas
			//TODO Send commande +MAJ état
			busy=1;
			serOutstring("Angle\n");
			return 1;
		}
		else
		{//Si on est a l'angle voulu on se déplace
			int dx=X_DES-X_POS;
			int dy=Y_DES-Y_POS;
			int Distance = sqrt(dx*dx+dy*dy);
			if(Distance==0)
			{//Rien a deplacer
				serOutstring("D0\n");
				return 0;
			}
			//TODO Send commande +MAJ état
			serOutstring("Distance\n");
			busy=1;
			return 1;
		}
}
// **************************************************************************************************
// MAIN
// **************************************************************************************************
                     /* size of local string buffer */ 



void main(void) {
	int i=0;
	char c;
     WDTCN     = 0xDE;
     WDTCN     = 0xAD;
	   Oscillator_Init();
	   Port_IO_Init();
	   
	   cfg_Clock_UART();
     cfg_UART0_mode1();
     init_Serial_Buffer();                            
     EA = 1;                              /* allow interrupts to happen */

	   serOutstring("Beginning\n");
	
while(1) {
	
		//UARTEvent();
	while ((c=serInchar())!=0) serOutchar(c);
	Analyse_Deplacement();
		
	} /* main */
}
