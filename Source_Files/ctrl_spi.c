
#include "ctrl_spi.h"

void setupSPI(void) {
    RPOR6bits.RP13R = 9; // SS1OUT pin
    RPOR7bits.RP14R = 8; // SCK1OUT pin
    RPOR7bits.RP15R = 7; // SDO1 pin

    SPI1CON1 = 0;               // spi control register 1
    SPI1CON1bits.DISSCK = 0;    // internal SPI clock
    SPI1CON1bits.DISSDO = 0;    // module controls data pin
    SPI1CON1bits.MODE16 = 0;    // 8-bit mode
    SPI1CON1bits.SMP = 0;       // sample data at end of output time
    SPI1CON1bits.CKE = 1;       // change data on act->idle clock
    SPI1CON1bits.SSEN = 0;      // no SSEN pin
    SPI1CON1bits.CKP = 0;       // active rising edge
    SPI1CON1bits.MSTEN = 1;     // master mode
    SPI1CON1bits.SPRE = 7;      // 1:1 secondary prescale
    SPI1CON1bits.PPRE = 1;      // 1:16 primary prescale

    SPI1CON2 = 0; // SPI control register 2
    
    SPI1STATbits.SPIEN = 1;         //enable SPI module
}

void writeSPI(char value) {
    while (SPI1STATbits.SPITBF);    //wait until fifo has open space (TODO: maybe do this with interrupts?)
    SPI1BUF = value;                //write value to SPI output buffer
}
