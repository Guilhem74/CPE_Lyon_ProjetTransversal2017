#include "ServoMoteur.h"
#include "Global.h"
#include "LIB_PROJET_T_ADC.h" 
#include "Lumiere.h" 

#include <c8051f020.h>   
extern int pulse_servo_H;
extern int angle;
extern int distance_avant, distance_arriere;
extern int compteur_telemetre, compteur_telemetre_arriere;
extern unsigned long int Time_in_ms;
extern char telemetre_enabled ;
extern int compteur_telemetre;
extern char enable_cpt_telemetre;
extern int intensite;
extern int duree_allumage;
extern int duree_extinction;
extern int nb_cycles;
void ISR_Timer2(void) interrupt 5 // interrupt toutes les 0.1ms
{

	static int cpt_servo_H = 0; 
	static int cmpt_time=0;
	TF2 = 0;
	P3|=0x10;
	cmpt_time++;
	if(cmpt_time==10)
	{
		Time_in_ms++;
		cmpt_time=0;
	}
	//////////////////////////////////////////
	// Servomoteur Horizontal   --> Crée une pulse de periode 20ms avec etat haut entre 0.5 et 2.8ms (lié à l'angle voulue)
	//////////////////////////////////////////
	if(cpt_servo_H > 200) // si on arrive a 20ms
	{
		cpt_servo_H = 0;
	}
	else if(cpt_servo_H <= pulse_servo_H) // etat haut de la pulse
	{
			P3 |= 0x40; // etat haut pour P3.6 qui represente le servo horizontal
	}
	else // etat bas, reste de la periode
	{
			P3 &= 0xBF; // eteind P3.6 le reste de la pulse
	}
	cpt_servo_H = cpt_servo_H + 1;
	//////////////////////////////////////////
	// Telemetre ultrason   --> Crée une pulse sur P6.4 et l'echo est renvoyé sur INT1 
	//////////////////////////////////////////
		if(compteur_telemetre ==0 )
	{
			P6 |= 0x10; // P6.4  et P6.5 à l'état haut pour 100us(pulse) pour declencher trig telemetre ultrason
	}
	else
	{
		P6 &= 0xEF; // P6.4 et P6.5 retourne à etat bas le reste du temps 
		
	}
	if(compteur_telemetre_arriere ==0 )
	{
			P6 |= 0x20; // P6.4  et P6.5 à l'état haut pour 100us(pulse) pour declencher trig telemetre ultrason
	}
	else
	{
		P6 &= 0xDF; // P6.4 et P6.5 retourne à etat bas le reste du temps 
		
	}
		compteur_telemetre++;//on compte
		compteur_telemetre_arriere++;
	
		//////////////////////////////////////////
	//Pilotage led en temps et en intensité en fonction de l'épreuve
	//////////////////////////////////////////
    pilotage_led(intensite, duree_allumage, duree_extinction, nb_cycles);
	P3&=0xEF;
	
}


void reception_telemetre_ultrason(void) interrupt 2//P2.5 ECHO
{

	distance_avant= 340*compteur_telemetre/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde à 340m/s, compteur incrémenté toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	if(distance_avant>25)
		distance_avant=ACQ_ADC();//Mesure de l'infrarouge , ainsi temps d'acquisition identique
	
		compteur_telemetre=-DELAY_ULTRASON; // reinitialisation compteur temps pulse-echo

	
	
	IE1=0; // remets flag a 0*/
}

void reception_telemetre_ultrason_arriere(void) interrupt 0
{
	distance_arriere= 340*compteur_telemetre_arriere/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde à 340m/s, compteur incrémenté toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	if(distance_arriere>25)
				distance_arriere=ACQ_ADC_2();//Mesure de l'infrarouge , ainsi temps d'acquisition identique

		compteur_telemetre_arriere=-DELAY_ULTRASON; // reinitialisation compteur temps pulse-echo
	
	

	IE0=0; // remets flag a 0*/
}



//////////////////////////////////////////
// Fonction permettant de fixer l'angle du servo horizontal
//////////////////////////////////////////
void Gen_Servo_Horizontal(int angle)
{
	if( (angle <= 90) && (angle >= -90) )
	{
		pulse_servo_H = (15*angle+1500)/100; // definit le nombre d'overflow  de 0.1ms timer2 (durée pulse) correspondant à l'angle
		// -90° = 0.9ms / 0° = 1.5ms / 90° = 2.1ms //
		// Equation regi par le systeme : tpulse = 15 + angle*0.07 et on multiplie le tout par 1000 afin d'eviter les arrondis puis on redivise par 1000
	}
	else
	{
		//printf("Veuillez entrez un angle entre -90° et 90°");
		pulse_servo_H = 0xFF;
	}
	
}


