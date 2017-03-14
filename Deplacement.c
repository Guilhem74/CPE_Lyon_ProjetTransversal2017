#include "Deplacement.h"
#include "Global.h"
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>

#include <stdlib.h>
#include <stdio.h>
extern char Busy_UART1;
extern int Vitesse_Robot;//pourcentage 	

void DeplacementContinu(int speed)
{
			char Envoi[40];
	sprintf(Envoi,"mogo 1:%d 2:%d \r",speed,speed);
		serOutstring_1(Envoi);
	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}

void DeplacementDistance(int distance,int speed)
{
				char Envoi[40];
				sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",distance,speed,distance,speed);
				serOutstring_1(Envoi);
	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}

void Tourner(int angle,int speed)
{
	int distanceD=angle*ANGLE_TO_ENC;
	char Envoi[40];
				sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",distanceD,speed,-distanceD,speed);
				serOutstring_1(Envoi);
	#if SERIAL0SPY
		serOutstring(Envoi);
	#endif
	Busy_UART1=1;
}