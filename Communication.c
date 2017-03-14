#include "Communication.h"
#include "Global.h"
#include <stdlib.h>

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
		serOutchar('D');
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
			serOutstring(">\r\n");
		}
		else
			serOutstring("Plz set a speed");
		Retour=TV;
	}
	else if(strcmp("A",First)==0)
	{//Avancer
		int Value=20;
		char Envoi[40];
		int Value_SS=sscanf(entree,"%s %d",First,&Value);
		if(Value_SS==2)
		{
			int Vitesse_Robot_temp=Value;
			sprintf(Envoi,"mogo 1:%d 2:%d \r",Vitesse_Robot_temp,Vitesse_Robot_temp);
		}
		else
			sprintf(Envoi,"mogo 1:%d 2:%d \r",Vitesse_Robot,Vitesse_Robot);
		
		serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;
		Retour=A;
	}
	else if(strcmp("B",First)==0)
	{//Reculer
		
		int Value=-20;
		char Envoi[40];
		int Value_SS=sscanf(entree,"%s %d",First,&Value);
		if(Value_SS==2)
		{
			int Vitesse_Robot_temp=Value;
			sprintf(Envoi,"mogo 1:%d 2:%d \r",-Vitesse_Robot_temp,-Vitesse_Robot_temp);
		}
		else
			sprintf(Envoi,"mogo 1:%d 2:%d \r",-Vitesse_Robot,-Vitesse_Robot);
		
		serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;
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
		
		
		char Envoi[70]="";
			sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",-Encodeur_90,Vitesse_Robot,Encodeur_90,Vitesse_Robot);
		
		serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;

		Retour=RD;
	}
	else if(strcmp("RG",First)==0)
	{//Rotation Gauche
		
		char Envoi[70]="";
			sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",Encodeur_90,Vitesse_Robot,-Encodeur_90,Vitesse_Robot);
		
		serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;
		Retour=RG;
	}
	else if(strcmp("RC",First)==0)
	{//Rotation complete
		char Envoi[70]="";
		char sens;
		int Value_SS=sscanf(entree,"%s %c",First,&sens);
		if(sens=='D')
			sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",-2*Encodeur_90,Vitesse_Robot,2*Encodeur_90,Vitesse_Robot);
		else if(sens=='G')
			sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",2*Encodeur_90,Vitesse_Robot,-2*Encodeur_90,Vitesse_Robot);
		else
		  serOutstring("Erreur de sens RC");

		
		serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;
		Retour=RC;
	}
	else if(strcmp("RA",First)==0)
	{//Rotation 
		
		char Envoi[70]="";
		char sens;
		int Value=20;
		int Sens_Val=-1;
		int Angle_Val=90*5.7;
		int Value_SS=sscanf(entree,"%s %c:%d",First,&sens,&Value);
		if(Value_SS==2)
		{//Sens spécifié
			serOutstring("2\r\n");
			if(sens=='D')
				Sens_Val=-1;
			else if(sens=='G')
				Sens_Val=1;
		}
		else if(Value_SS==3)
		{//Sens et valeur angle spécifié
			serOutstring("3\r\n");
				if(sens=='D')
				Sens_Val=-1;
			else if(sens=='G')
				Sens_Val=1;
			
			Angle_Val=Value*5.7;
		}
		
		
			sprintf(Envoi,"digo 1:%d:%d 2:%d:%d \r",Sens_Val*Angle_Val,Vitesse_Robot,-Sens_Val*Angle_Val,Vitesse_Robot);
serOutstring_1(Envoi);
		serOutstring(Envoi);
		Busy_UART1=1;
		Retour=RA;
	}
	else if(entree[0]=='A'&&entree[1]=='S'&&entree[2]=='S')
	{//Acquisition son
		Retour=ASS;
	}
	else if(entree[0]=='G')
	{//Deplacement BR
		Retour=G;
	}
	else if(entree[0]=='M'&&entree[1]=='I')
	{//Mesure courant
		Retour=MI;
	}
	else if(entree[0]=='M'&&entree[1]=='E')
	{//Mesure Energie
		Retour=ME;
	}
	else if(entree[0]=='I'&&entree[1]=='P'&&entree[2]=='O')
	{//Init pos
		Retour=IPO;
	}
	else if(entree[0]=='P'&&entree[1]=='O'&&entree[2]=='S')
	{//Pos
		Retour=POS;
	}
	else if(entree[0]=='M'&&entree[1]=='O'&&entree[2]=='U')
	{//Detection obstacle unique
		Retour=MOU;
	}
	else if(entree[0]=='M'&&entree[1]=='O'&&entree[2]=='B')
	{//Detection par balayage
		Retour=MOB;
	}
	else if(entree[0]=='S'&&entree[1]=='D')
	{//Generation son
		Retour=SD;
	}
	else if(entree[0]=='L')
	{//Allumage pointeur
		Retour=L;
	}
	else if(entree[0]=='L'&&entree[1]=='S')
	{//Fin allumage pointeur
		Retour=LS;
	}
	else if(entree[0]=='C'&&entree[1]=='S')
	{//Pilotage servo
		Retour=CS;
	}
	else if(entree[0]=='P'&&entree[1]=='P'&&entree[2]=='H')
	{//prise photo
		Retour=PPH;
	}
	else if(entree[0]=='S'&&entree[1]=='P'&&entree[2]=='H')
	{//Arret prise photo
		Retour=SPH;
	}
	else if(entree[0]=='A'&&entree[1]=='U'&&entree[2]=='X')
	{//cmd aux
		Retour=AUX;
	}
	else
	{
		Retour=Empty;
	}
	
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
   