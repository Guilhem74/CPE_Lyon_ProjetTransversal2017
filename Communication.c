#include "Communication.h"

#include "Deplacement.h"
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>
extern char Busy_UART1;
extern int Vitesse_Robot;//pourcentage 	
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
			 Retour_Serializer Retour=	Parseur_Uart_1(Reception_Uart1);
		 // serOutstring(Retour);//ici recopie serial
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
	#define SIZE_BUFF_RECEPT_UART0 20
	static char Reception_Uart0[SIZE_BUFF_RECEPT_UART0];
	static unsigned char Value_Rec0=0;
	char  c;
		int i=0;
	if ((c=serInchar())!=0)
	 {
		 if(c=='\r')//Fin de commande putty
		 {//Message de com fin de reception pour PC
			 //TODO ACTION PARSEUR
			Message_Commande Retour=	Parseur_Uart_0(Reception_Uart0);
//Check 
//			 serOutstring(Retour);
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
 
Message_Commande Parseur_Uart_0(char entree[])
{
    Message_Commande Retour=Empty;
	char First[4];

	int j=0;
	sscanf(entree,"%s ",First);
	
	if(strcmp("D",First)==0)
	{
		
		Retour=D;
	}
	else if(entree[0]=='E')
	{//Fin d'épreuve
		Retour=E;
	}
	else if(strcmp("Q",First)==0)
	{//Arret d'urgence
		serOutstring_1("stop\r");
		Retour=Q;
	}	
	else if(strcmp("TV",First)==0)
	{//Reglage vitesse
		int Value=20;
		int Value_SS=sscanf(entree,"%s %d",First,&Value);
		
		if(Value_SS==2)
		{
			Vitesse_Robot=Value;
			Retour=TV;
		}
		else
			Retour=Empty;
		
	}
	else if(strcmp("A",First)==0)
	{//Avancer
		int Value=20;
		int Value_SS=sscanf(entree,"%s %d",First,&Value);
		if(Value_SS==2)
		{
			DeplacementContinu(Value);
		}
		else
			DeplacementContinu(Vitesse_Robot);
		
		Retour=A;
	}
	else if(strcmp("B",First)==0)
	{//Reculer
		
		int Value=-20;
		int Value_SS=sscanf(entree,"%s %d",First,&Value);
		if(Value_SS==2)
		{
			DeplacementContinu(-Value);
		}
		else
			DeplacementContinu(-Vitesse_Robot);
		
		Retour=B;
	}
	else if(strcmp("S",First)==0)
	{//STOP
	
		serOutstring_1("stop\r");
		Busy_UART1=1;
		Retour=S;
	}
	else if(strcmp("RD",First)==0)
	{//Rotation Droite
		Tourner(-90,Vitesse_Robot);
		Retour=RD;
	}
	else if(strcmp("RG",First)==0)
	{//Rotation Gauche
		Tourner(-90,Vitesse_Robot);
		Retour=RG;
	}
	else if(strcmp("RC",First)==0)
	{//Rotation complete
		char sens;
		
		int Value_SS=sscanf(entree,"%s %c",First,&sens);
		Retour=RC;
		if(sens=='D')
				Tourner(180,Vitesse_Robot);
			else if(sens=='G')
				Tourner(-180,Vitesse_Robot);
		else
		{
				Retour=Empty;
		}
		
	}
	else if(strcmp("RA",First)==0)
	{//Rotation 
		
		char sens;
		int Value=20;
		int Sens_Val=-1;
		int Angle_Val=90;
		int Value_SS=sscanf(entree,"%s %c:%d",First,&sens,&Value);
		if(Value_SS>=2)
		{//Sens spécifié
			if(sens=='D')
				Sens_Val=-1;
			else if(sens=='G')
				Sens_Val=1;
		}
		if(Value_SS==3)
		{//Valeur spécifié
			Angle_Val=Value;
		}
		Tourner(Sens_Val*Angle_Val,Vitesse_Robot);
		Retour=RA;
	}
	else if(strcmp("ASS",First)==0)
	{//Acquisition son
		Retour=ASS;
	}
	else if(strcmp("G",First)==0)
	{//Deplacement BR
		Retour=G;
	}
	else if(strcmp("MI",First)==0)
	{//Mesure courant
		Retour=MI;
	}
	else if(strcmp("ME",First)==0)
	{//Mesure Energie
		Retour=ME;
	}
	else if(strcmp("IPO",First)==0)
	{//Init pos
		Retour=IPO;
	}
	else if(strcmp("POS",First)==0)
	{//Pos
		Retour=POS;
	}
	else if(strcmp("MOU",First)==0)
	{//Detection obstacle unique
		Retour=MOU;
	}
	else if(strcmp("MOB",First)==0)
	{//Detection par balayage
		Retour=MOB;
	}
	else if(strcmp("SD",First)==0)
	{//Generation son
		Retour=SD;
	}
	else if(strcmp("L",First)==0)
	{//Allumage pointeur
		Retour=L;
	}
	else if(strcmp("LS",First)==0)
	{//Fin allumage pointeur
		Retour=LS;
	}
	else if(strcmp("CS",First)==0)
	{//Pilotage servo
		Retour=CS;
	}
	else if(strcmp("PPH",First)==0)
	{//prise photo
		Retour=PPH;
	}
	else if(strcmp("SPH",First)==0)
	{//Arret prise photo
		Retour=SPH;
	}
	else if(strcmp("AUX",First)==0)
	{//cmd aux
		Retour=AUX;
	}
	else
	{
		Retour=Empty;
		
	}
	if(Retour!=Empty)
		Ready_To_Continue();
	else
		Failed();
	
	return Retour;
}
Retour_Serializer Parseur_Uart_1(char entree[])
{
    Retour_Serializer type=EMPTY;
	if(strstr(entree,"NACK")!= NULL)
	{
              type=NACK;
	}
	else if(strstr(entree,"ACK")!= NULL)
	{
		
              type=ACK;
	}
	else if(strstr(entree,"0")!= NULL)
	{
              type=FALSE;
	}
	else if(strstr(entree,"1")!= NULL)
	{
              type=TRUE;
	}

	return type;

}
void Ready_To_Continue()
{
	serOutstring("\r\n>");
}
void Failed()
{
	serOutstring("\r\n#");
}