
#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funTX.h"

#define VELOCIDAD 32        // 9600 baudios
#define PIN_TX (1<<7)
#define PRIORIDAD 3
#define SUBPRIORIDAD 0

#define TAM_MAX 80
static char tx[TAM_MAX];
static int i_tx = 0;

void InicializarUART_TX(void) {
    
    U1BRG = VELOCIDAD;
    
    IFS1bits.U1TXIF = 0;
    IEC1bits.U1TXIE = 1;
    
    IPC8bits.U1IP = PRIORIDAD;
    IPC8bits.U1IS = SUBPRIORIDAD;
    
    ANSELBCLR = PIN_TX;
    TRISBCLR = PIN_TX;
    LATBSET = PIN_TX;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1;
    SYSKEY = 0x11112222;
    
    U1STAbits.UTXISEL = 2;
    
    U1STAbits.UTXEN = 1;
    
    U1MODE = 0x8000;

}

__attribute__((vector(32),interrupt(IPL3SOFT),nomips16))
void InterrupcionUART1_TX(void) {
    if (IFS1bits.U1TXIF == 1) {
        IEC1bits.U1TXIE = 0;
        i_tx = 0;
        tx[i_tx] = '\0';
        
    } else {
        U1TXREG = tx[i_tx];
        i_tx++;
    }
    IFS1bits.U1TXIF = 0;
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

