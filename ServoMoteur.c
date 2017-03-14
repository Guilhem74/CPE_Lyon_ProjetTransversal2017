#include "ServoMoteur.h"
#include "Global.h"
#include "LIB_PROJET_T_ADC.h" 

#include <c8051f020.h>   
extern int pulse_servo_H;
extern int angle;
extern int distance_ultrason;
extern int distance_infrarouge;
extern int compteur_telemetre;

void ISR_Timer2(void) interrupt 5 // interrupt toutes les 0.1ms
{

	static int cpt_servo_H = 0; 
	//////////////////////////////////////////
	// Servomoteur Horizontal   --> Cr�e une pulse de periode 20ms avec etat haut entre 0.5 et 2.8ms (li� � l'angle voulue)
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
	// Telemetre ultrason   --> Cr�e une pulse sur P6.4 et l'echo est renvoy� sur INT1 
	//////////////////////////////////////////
	if(compteur_telemetre ==0 )
	{
			P6 |= 0xF0; // P6.4 � l'�tat haut pour 100us(pulse) pour declencher trig telemetre ultrason
	}
	else
	{
		P6 &= 0x0F; // P6.4 retourne � etat bas le reste du temps 
		
	}
		compteur_telemetre++;//on compte
	TF2 = 0;
}

void reception_telemetre_ultrason(void) interrupt 2
{
	distance_ultrason= 340*compteur_telemetre/(200) - 7; //calcul distance entre l'obstacle et le robot:
	//onde � 340m/s, compteur incr�ment� toutes les 0.1ms 
	// On multiplie 340 par 100 pour avoir cm/s // On divise par 10000 compteur telemetre pour avoir en secondes et on divise par 2 (aller retour ECHO)
	compteur_telemetre=-DELAY_ULTRASON; // reinitialisation compteur temps pulse-echo
	
	
		distance_infrarouge=ACQ_ADC();//Mesure de l'infrarouge , ainsi temps d'acquisition identique

	IE1=0; // remets flag a 0*/
}

//////////////////////////////////////////
// Fonction permettant de fixer l'angle du servo horizontal
//////////////////////////////////////////
void Gen_Servo_Horizontal(int angle)
{
	if( (angle <= 90) && (angle >= -90) )
	{
		pulse_servo_H = (15*angle+1500)/100; // definit le nombre d'overflow  de 0.1ms timer2 (dur�e pulse) correspondant � l'angle
		// -90� = 0.9ms / 0� = 1.5ms / 90� = 2.1ms //
		// Equation regi par le systeme : tpulse = 15 + angle*0.07 et on multiplie le tout par 1000 afin d'eviter les arrondis puis on redivise par 1000
	}
	else
	{
		//printf("Veuillez entrez un angle entre -90� et 90�");
		pulse_servo_H = 0xFF;
	}
	
}