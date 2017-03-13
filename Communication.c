#include "Communication.h"
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
			  serOutstring(Reception_Uart1);//ici recopie serial
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
	#define SIZE_BUFF_RECEPT_UART0 5
	static char Reception_Uart0[SIZE_BUFF_RECEPT_UART0];
	static unsigned char Value_Rec0=0;
	char  c;
		int i=0;
	if ((c=serInchar())!=0)
	 {
		 if(c=='\r')//Fin de commande putty
		 {//Message de com fin de reception pour PC
			 //TODO ACTION PARSEUR

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
    Message_Commande type=Empty;

      /* Recherche la copie exacte de str2 dans str1 */
      if(strstr(entree,"D") != NULL) //D
      {
          type=D;
          if(strstr(entree,"RD") != NULL)
              type=RD;
          if(strstr(entree,"SD") != NULL)
              type=SD;

      }
      if(strstr(entree,"E") != NULL)//E
      {
          type=E;
          if(strstr(entree,"ME") != NULL)
              type=ME;

      }
      if(strstr(entree,"Q") != NULL) //Q
          type=Q;
      if(strstr(entree,"A") != NULL) //A
      {
          type=A;
          if(strstr(entree,"RA") != NULL)
              type=RA;
          if(strstr(entree,"ASS") != NULL)
              type=ASS;
          if(strstr(entree,"AUX") != NULL)
              type=AUX;
      }
      if(strstr(entree,"B") != NULL) //B
      {
          type=B_message;
          if(strstr(entree,"MOB") != NULL)
              type=MOB;
      }
      if(strstr(entree,"S") != NULL)//S
      {
          type=S;
          if(strstr(entree,"ASS") != NULL)
              type=ASS;
          if(strstr(entree,"POS") != NULL)
              type=POS;
          if(strstr(entree,"SD") != NULL)
              type=SD;
          if(strstr(entree,"LS") != NULL)
              type=LS;
          if(strstr(entree,"CS") != NULL)
              type=CS;
          if(strstr(entree,"SPH") != NULL)
              type=SPH;
      }
      if(strstr(entree,"G") != NULL)//G
          type=G;
      if(strstr(entree,"L") != NULL)//L
      {
          type=L;
          if(strstr(entree,"LS") != NULL)
                  type=LS;
      }
      if(strstr(entree,"TV") != NULL) //TV
          type=TV;
      if(strstr(entree,"RG") != NULL) //RG
          type=RG;
      if(strstr(entree,"RC") != NULL) //RC
          type=RC;
      if(strstr(entree,"MI") != NULL) //MI
          type=MI;
      if(strstr(entree,"IPO") != NULL) //IPO
          type=IPO;
      if(strstr(entree,"MOU") != NULL) //MOU
          type=MOU;
      if(strstr(entree,"PPH") != NULL) //PPH
          type=PPH;

    return type;
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
   