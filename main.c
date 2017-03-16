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

#include "ServoMoteur.h"
#include "LIB_PROJET_T_Config_Globale.h"
#include "Communication.h"
#include "Deplacement.h"
#include "ServoMoteur.h"
#include <string.h>
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif
#include <stdlib.h>
#include "LIB_PROJET_T_ADC.h" 
sbit BP = P3^7;     


char Busy_UART1=0;
char Mooving=0;
char Deplacement_Demande=0;
char Ready=0;
int Vitesse_Robot=20;//pourcentage 	
int pulse_servo_H = 15,pulse_servo_V=15; // correspond à un angle de 0°
int angle = 0;
int distance_avant = 0;
int distance_arriere = 0;
int compteur_telemetre=0,compteur_telemetre_arriere=0;	

int intensite=0;
int duree_allumage=0;
int duree_extinction=0;
int nb_cycles=0;

unsigned long int Time_in_ms=0;
int X_POS=0,Y_POS=0,A_POS=0,X_DEST=0,Y_DEST=0,A_DEST=0,A_FIN=0;
int Params_Change=-1;//Permet de specifier le parametre a changer


void main(void) {


	unsigned long int Time_PAST=0;
	//char Envoi[40];

	Init_Device();
	cfg_Clock_UART();
		cfg_UARTS_mode1();
		init_Serial_Buffer();   
		init_Serial_Buffer_1();	
		EA = 1;   

		serOutstring("\r\nINIT 8051 DONE\r\n");
Gen_Servo_Horizontal(0);
	Ready_To_Continue();
P2MDOUT=0x00;//Force P2 en drain ouvert
	P2=0xFF;
		

	while(1) {
	
	SerialEvent1();
	SerialEvent0();
		if(Time_in_ms>Time_PAST+10)//Boucle de 10 ms min
		{
				
			//sprintf(Envoi,"\r\nCapteur X:%d %d \r\n",distance_avant,distance_arriere);
			//sprintf(Envoi,"\r\nCapteur Arriere:%d %d \r\n",distance_ultrason_arriere,distance_infrarouge_arriere);
			//serOutstring(Envoi);
			Analyse_Deplacement();
			Time_PAST=Time_in_ms;
		}

	} 
}


