#include "ServoMoteur.h"
#include <c8051f020.h>   
int pulse_servo_H = 15; // correspond à un angle de 0°
int angle = 0;


void ISR_Timer2(void) interrupt 5 // interrupt toutes les 0.1ms
{

	static int cpt_servo_H = 0; 
	
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
	
	TF2 = 0;
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