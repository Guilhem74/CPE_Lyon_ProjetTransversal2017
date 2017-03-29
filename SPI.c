#include SPI.h

//-----------------------------------------------------------------------------
// SPI0_Init
//-----------------------------------------------------------------------------
//
// Configure SPI0 8-bit, 2MHz SCK, Maitre, interruption SPI0, front montant

void SPI0_Init (void)
{
 SPI0CFG = 0x07; // Donnée lu sur premiere front montant horloge
 // 8-bit de données
 SPI0CN = 0x03; //Maitre; SPI actif; drapeau désactivé

 SPI0CKR = SYSCLK/2/2000000; // <= 2MHz 

 //EE_Ready = TRUE; // post SPI0/EEPROM available
 EIE1 |= 0x01; // active interruption du SPI SPI0 
}

//-----------------------------------------------------------------------------
// EE_Read
//-----------------------------------------------------------------------------
//
// This routine reads and returns a single EEPROM byte whose address is
// given in <Addr>.
//
unsigned char SPI_Read (unsigned Addr)
{
unsigned char retval; // value to return
	CS = 0; // select slave
	Timer0_us (1); // wait at least 250ns (CS setup time)
	
	// transmit READ opcode
	SPIF = 0;
	SPI0DAT = READ_SPI;//Code pour le protocle SPI
	while (SPIF == 0);
	
	// Adresse esclave MSB-first
	SPIF = 0; // Transmission du MSB de  l'addresse
	SPI0DAT = (Addr >> 8);
	while (SPIF == 0);
	
	SPIF = 0; // Transmission du LSB de  l'addresse
	SPI0DAT = Addr;
	while (SPIF == 0);
	
	// initiate dummy transmit to read data
	SPIF = 0;
	SPI0DAT = 0;
	while (SPIF == 0);

	retval = SPI0DAT; // Lecture de la donnée 
	Timer0_us (1); //Attente de 250ns (CS hold time)

	CS = 1; // de-select slave
	Timer0_us (1); // wait at least 500ns (CS disable time)
	return retval;
}
//-----------------------------------------------------------------------------
// EE_Write
//-----------------------------------------------------------------------------
//
// This routine writes a single EEPROM byte <value> to address <Addr>. Here
// we implement post-write polling, and return once the write operation has
// completed. This prevents us from having to poll before an EEPROM Read
// or Write operation.
//
void SPI_Write (unsigned Addr, unsigned char value)
{
	 CS = 0; // select slave
	 Timer0_us (1); // wait at least 250ns (CS setup time)
	 
	 // transmit WREN (Write Enable) opcode
	 SPIF = 0;
	 SPI0DAT = WREN_SPI;
	 while (SPIF == 0);
	 
	 Timer0_us (1); // wait at least 250ns (CS hold time)
	 CS = 1; // de-select slave to set WREN latch
	 Timer0_us (1); // wait at least 500ns (CS disable time)
	 CS = 0; // select slave
	 Timer0_us (1); // wait at least 250ns (CS setup time)
	 
	 // transmit WRITE opcode
	 SPIF = 0;
	 SPI0DAT = WRITE_SPI;
	 while (SPIF == 0);
	 
	 // transmit Address MSB-first
	 SPIF = 0; // transmit MSB of address
	 SPI0DAT = (Addr >> 8);
	 while (SPIF == 0);
	 SPIF = 0; // transmit LSB of address
	 SPI0DAT = Addr;
	 while (SPIF == 0);
	 
	 // transmit data
	 SPIF = 0;
	 SPI0DAT = value;
	 while (SPIF == 0);
	 Timer0_us (1); // wait at least 250ns (CS hold time)
	 CS = 1; // deselect slave (initiate slave write cycle)
	 
	 // now poll Read Status Register (RDSR) for Write operation complete
	 do {
		 Timer0_us (1); // wait at least 500ns (CS disable
		 // time)
		 CS = 0; // select slave to begin polling
		 Timer0_us (1); // wait at least 250ns (CS setup time)
		 SPIF = 0;
		 SPI0DAT = RDSR_SPI; // send Read Status register opcode
		 while (SPIF == 0);
		 SPIF = 0;
		 SPI0DAT = 0; // dummy write to read status register
		 while (SPIF == 0);
		 Timer0_us (1); // wait at least 250ns (CS hold
		 // time)
		 CS = 1; // de-select EEPROM
	 } while (SPI0DAT & 0x01); // poll until WIP (Write In
	 // Progress) bit goes to ‘0’
	 Timer0_us (1); // wait at least 500ns (CS disable
	 // time)
}