#include "Ensemble_Systeme.h"
extern xdata Ensemble_Systeme_Tri S;
void Initialisation_Ensemble_Systeme(void)
{
	Colis Colis_Vide={0,0,0,0,0};
	S.Nbr_TypeA=0;
	S.Nbr_TypeB=0;
	S.Nbr_TypeC=0;
	S.Nbr_HC=0;
	S.Nbr_TypeA_pesee=0;
	S.Nbr_TypeB_pesee=0;
	S.Nbr_TypeC_pesee=0;
	S.Colis4[0]=Colis_Vide;
	S.Colis4[1]=Colis_Vide;
	S.Colis4[2]=Colis_Vide;
	S.Colis4[3]=Colis_Vide;
	S.Balance=Libre;
}
void Marquage_Colis()
{
}

char Changement_Etat_Barriere(char etat)
{//retourne 1 si on change d'état
	static etat_precedent=0;
	if(etat!=etat_precedent)
	{
		etat_precedent=1-etat_precedent;
		return 1;
	}
	else
	{
		return 0;
	}
}
char Barriere_Optique(void)
{
	return 1-Read_P2_2();
}

void Analyse_detection(void)
{
	char Detection= Barriere_Optique();//1= COlis 0= Rien
	static int delai_detection=50;
		if(Detection==1&& Changement_Etat_Barriere(Detection))
	{// On vient de commencer la detection d'un paquet
		//verification des 25cm
		if(delai_detection<48)//48*5ms ~ 240 ms par sécurite dus a l'imperfection de l'interruption~ 25 cm 
		{
			Set_Erreur();
		}
		delai_detection=1;
	}
	else if(Detection==1&& !Changement_Etat_Barriere(Detection))//On continue la detection d'un paquet
		delai_detection++;
	else if(Detection==0&& Changement_Etat_Barriere(Detection))
	{//Un paquet vient de finir de passer
		//Verification gabarit , enregistrement taille ...
		int Taille=delai_detection*5/10;//en Cm
		Stockage_colis(Taille);
		delai_detection=1;
	}
	else
		delai_detection++;
}
void Analyse_colis_convoyeur(void)
{
	int i=1;
Colis Colis_Vide={0,0,0,0,0};
	for(i=1;i<4;i++)
	{
		if(Conversion_horloge_en_centiemes()==S.Colis4[i].heure_poussee && S.Colis4[i].Valide==1)
		{//Si on a trouvé un colis dispo a pousser
			if(S.Balance==Libre)
			{//La balance est dispo
				S.Colis4[0]=S.Colis4[i];//sauvegarde du colis choisis dans la case 0
				S.Colis4[i]=Colis_Vide;//suppression du colis dans la file d'attente
				S.Balance=Chargement;
				Pulse_P20();//Activation piston
			}
		}
		if(Conversion_horloge_en_centiemes() > S.Colis4[i].heure_poussee)
		{//On a dépassé l'heure de poussée -> On ne poussera jamais le colis
			
			S.Colis4[i]=Colis_Vide;
		}
			
	}
}
void Stockage_colis(int Taille)
{
	static int position_colis=1;
	if(position_colis==4)
	{
		position_colis=1;
	}
	if(Taille>9&&Taille<11)
	{
		S.Nbr_TypeA++;
		Enregistrement_Colis(position_colis, 1, 1);
		position_colis++;
	}
	else if(Taille>14&&Taille<16)
	{
		S.Nbr_TypeB++;
		Enregistrement_Colis(position_colis, 2, 1);
		position_colis++;
	}
	else if(Taille>19&&Taille<21)
	{
		S.Nbr_TypeC++;
		Enregistrement_Colis(position_colis, 3, 1);
		position_colis++;
	}
	else
	{
		S.Nbr_HC++;
		Enregistrement_Colis(position_colis, 4, 0);
	}
}
void Enregistrement_Colis(char Position_file, char Type, char Correct)
{
	
		S.Colis4[Position_file].Poids=0;
		S.Colis4[Position_file].Valide=Correct;
		S.Colis4[Position_file].Type=Type;
		S.Colis4[Position_file].heure_detection=Conversion_horloge_en_centiemes();
		S.Colis4[Position_file].heure_poussee=Conversion_horloge_en_centiemes()+96;//le colis doit parcourir 48 cm pour etre au millieu du piston soit 96 tick de 5ms
}