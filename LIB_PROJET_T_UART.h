/*---------------------------------------------------------------------------
;
;
;
;
; 	FILE NAME  	: LIB_BSE_UART
; 	TARGET MCUs	: C8051F020, 
; 	DESCRIPTION	: Fonctions Bas niveau pour le TP EMBARQUE
;
; 	REVISION 1.0
;
;---------------------------------------------------------------------------*/


#ifndef __LIB_BSE_UART__
#define __LIB_BSE_UART__
#define NOP()                  	_nop_()
#define NOP2()                  {NOP(); NOP();}
#define NOP4()                  {NOP2(); NOP2();}
#define NOP8()                  {NOP4(); NOP4();}
#define NOP16()                 {NOP8(); NOP8();}
#define NOP32()                 {NOP16(); NOP16();}
#define NOP64()                 {NOP32(); NOP32();}
#define NOP128()                {NOP64(); NOP64();}
#define NOP256()                {NOP128(); NOP128();}
#define NOP512()                {NOP256(); NOP256();}
#define NOP1024()                {NOP512(); NOP512();}
#define NOP2048()                {NOP1024(); NOP1024();}
#define NOP4096()                {NOP2048(); NOP2048();}
#define NOP8192()                {NOP4096(); NOP4096();}
#define NOP16384()                {NOP8192(); NOP8192();}
void CFG_UART(void);

void CFG_UART0_CLOCK(void);

void CFG_UART0(void);
char Putchar(char c, unsigned char csg_tempo);

char Getchar(void);
char Send_String(char* char_ptr);
void test_uart(void);
#endif