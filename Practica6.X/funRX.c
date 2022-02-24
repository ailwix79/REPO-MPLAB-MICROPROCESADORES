
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funRX.h"

#define VELOCIDAD 32        // 9600 baudios
#define PIN_RX (1<<13)
#define PRIORIDAD 3
#define SUBPRIORIDAD 0

void InicializarUART(void) {
    
    U1BRG = VELOCIDAD;
    
    IFS1bits.U1RXIF = 0;
    IEC1bits.U1RXIE = 1;
    
    IPC8bits.U1IP = PRIORIDAD;
    IPC8bits.U1IS = SUBPRIORIDAD;
    
    ANSELBCLR = PIN_RX;
    TRISBSET = PIN_RX;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    U1RXR = 3;
    SYSKEY = 0x11112222;
    
    U1STAbits.URXISEL = 0;
    
    U1STAbits.URXEN = 1;
    
    U1MODE = 0x8000;

}

static char rx ='\0';

__attribute__((vector(32),interrupt(IPL3SOFT),nomips16))
void InterrupcionUART1(void) {
    if (IFS1bits.U1RXIF == 1) {
        rx = U1RXREG;
        IFS1bits.U1RXIF = 0;
    }
}

char getRX(void) {
    char rx_c = '\0';
    
    asm("   di");
    rx_c = rx;
    rx = '\0';
    asm("   ei");
    
    return rx_c;
}
