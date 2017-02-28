
#ifndef Ensemble_Systeme
#define Ensemble_Systeme
#include "LIB_BSE_GPIO.h"
#include "LIB_BSE_Timers.h"
typedef enum Systeme_de_pesee{
	Libre,
	Chargement,
	Pesee,
	Attente_pesee,
	Fin_pesee,
	Marquage,
	Pousse,
	Pousse_attente,
	Erreur
}Systeme_de_pesee;

typedef struct Colis
{ 	
	int Poids;
	char Valide;
	char Type;
	unsigned long int heure_detection;//centième de seconde 
	unsigned long int heure_poussee;
}Colis;

typedef struct Ensemble_Systeme_Tri
{
	int Nbr_TypeA, Nbr_TypeB, Nbr_TypeC,Nbr_HC,Nbr_TypeA_pesee,Nbr_TypeB_pesee,Nbr_TypeC_pesee;
	 Colis Colis4[4]; 
	 Systeme_de_pesee Balance;
}Ensemble_Systeme_Tri;

void clear_RTC(void);
void Initialisation_Ensemble_Systeme(void);
void Marquage_Colis(void);
char Barriere_Optique(void);
void Enregistrement_Colis(char Position_file, char Type, char Correct);
void Analyse_detection(void);
void Stockage_colis(int Taille);
void Analyse_colis_convoyeur(void);
void Enregistrement_Colis(char Position_file, char Type, char Correct);
#endif
