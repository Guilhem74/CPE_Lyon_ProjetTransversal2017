#ifndef __Communication__h
#define __Communication__h
#include <string.h>
#include <UART0_RingBuffer_lib.h>
#include <UART1_RingBuffer_lib.h>
#ifndef CFG_Globale
  #define CFG_Globale
  #include <CFG_Globale.h>
#endif

enum Message_Commande {Empty,D, E, Q, TV, A, B_message, S, RD, RG, RC,RA,G,ASS,MI,ME,IPO,POS,MOU,MOB,SD,L,LS,CS,PPH,SPH,AUX};
enum Retour_Serializer {EMPTY,ACK,NACK,TRUE,FALSE};
typedef enum Retour_Serializer Retour_Serializer;
typedef enum Message_Commande Message_Commande;
Message_Commande Parseur_Uart_0();
Retour_Serializer Parseur_Uart_1();
void SerialEvent0();
void SerialEvent1();

#endif