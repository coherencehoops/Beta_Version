
// Guard condition so that contents of file are not included more than once.  
#ifndef CTRL_SPI
#define	CTRL_SPI

#include <p24Fxxxx.h>
#include <xc.h>

void setupSPI(void);
void writeSPI(char);

#endif	/* CTRL_SPI */

