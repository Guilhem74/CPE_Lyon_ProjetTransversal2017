#include "ServoMoteur.h"
#include "Global.h"
#include "LIB_PROJET_T_ADC.h" 

#include <c8051f020.h>   
extern int pulse_servo_H;
extern int angle;
extern int distance_ultrason;
extern int distance_infrarouge;
extern int compteur_telemetre;
extern unsigned long int Time_in_ms;
extern int distance_ultrason ;
extern char telemetre_enabled ;
extern int compteur_telemetre;
extern char enable_cpt_telemetre;
void ISR_Timer2(void) interrupt 5 // interrupt toutes les 0.1ms
{

	static int cpt_servo_H = 0; 
	static int cmpt_time=0;
	static int cpt_telemetre_interne = 0;
	cmpt_time++;
	if(cmpt_time==10)
	{
		Time_in_ms++;
		cmpt_time=0;
	}
	//////////////////////////////////////////
	// Servomoteur Horizontal   --> Crée une pulse de periode 20ms avec etat haut entre 0.5 et 2.8ms (lié à l'angle voulue)
	//////////////////////////////////////////
	if(cpt_servo_H >= 200) // si on arrive a 20ms
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
	if(telemetre_enabled && (cpt_telemetre_interne < 1) )
	{
			P6 |= 0xF0; // P6.4 à l'état haut pour 100us(pulse) pour declencher trig telemetre ultrason
			telemetre_enabled = 0;
			enable_cpt_telemetre = 1;
	}
	else
	{
		P6 &= 0x0F; // P6.4 retourne à etat bas le reste du temps 
		cpt_telemetre_interne++;
	}
		
	if(cpt_telemetre_interne >= 50)
	{
		cpt_telemetre_interne = 0;
		telemetre_enabled = 1;
	}
	
	if(enable_cpt_telemetre)
	{
		compteur_telemetre++;
	}
	TF2 = 0;
}


void reception_telemetre_ultrason(void) interrupt 2//P2.5 ECHO
{

	distance_ultrason= 340*compteur_telemetre/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde à 340m/s, compteur incrémenté toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	
	
	
	enable_cpt_telemetre = 0; // on arrete de compter le temps entre la pulse et reception echo
	compteur_telemetre=0; // reinitialisation compteur temps pulse-echo
	
				
	
	
	IE1=0; // remets flag a 0*/
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