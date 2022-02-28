
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funTXRX.h"

#define VELOCIDAD 32        // 9600 baudios
#define PIN_RX (1<<13)
#define PIN_TX (1<<7)
#define PRIORIDAD 3
#define SUBPRIORIDAD 1

#define TAM_MAX 80

void InicializarUART_TX_RX(void) {
    
    U1BRG = VELOCIDAD;
    
    IFS1bits.U1RXIF = 0;
    IEC1bits.U1RXIE = 1;
    IFS1bits.U1TXIF = 0;
    
    IPC8bits.U1IP = PRIORIDAD;
    IPC8bits.U1IS = SUBPRIORIDAD;
    
    ANSELBCLR = PIN_RX;
    TRISBSET = PIN_RX;
    
    ANSELBCLR = PIN_TX;
    TRISBCLR = PIN_TX;
    LATBSET = PIN_TX;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    U1RXR = 3;
    RPB7R = 1;
    SYSKEY = 0x11112222;
    
    U1STAbits.URXISEL = 0;
    U1STAbits.UTXISEL = 2;
    
    U1STAbits.URXEN = 1;
    U1STAbits.UTXEN = 1;

    U1MODE = 0x8000;
}

static char rx = '\0';
static char tx[TAM_MAX];
static int i_tx = 0;

__attribute__((vector(32),interrupt(IPL3SOFT),nomips16))
void InterrupcionUART1(void) {
    if (IFS1bits.U1RXIF == 1) {
        rx = U1RXREG;
        IFS1bits.U1RXIF = 0;
    }
    
    if (IFS1bits.U1TXIF == 1) {
        if(tx[i_tx] == '\0') {
            IEC1bits.U1TXIE = 0;
            i_tx = 0;
            tx[i_tx] = '\0';
        
        } else {
            U1TXREG = tx[i_tx];
            i_tx++;
        }
        IFS1bits.U1TXIF = 0;
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

void setTX(char *ps) {
    char *pc;
    pc = tx;
    while (*ps != '\0') {
        *pc = *ps;
        pc++;
        ps++;
    }
    IEC1bits.U1TXIE = 1;
}
