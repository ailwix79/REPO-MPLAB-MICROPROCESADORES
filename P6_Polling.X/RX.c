/* 
 * File:   RX.c
 * Author: Alejandro
 *
 * Created on 27 de febrero de 2022, 23:22
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"

/*
 * 
 */

#define PIN_RX (1<<13)
#define MASCARA_LEDS 15


void InicializarUART_RX(void) {
    U1BRG = 32;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    U1RXR = 3;
    SYSKEY = 0x11112222;
    
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;
}

void InicializarTarjeta_RX(void) {
    ANSELBCLR = PIN_RX;
    ANSELCCLR = MASCARA_LEDS;
    TRISBSET = PIN_RX;
    TRISCCLR = MASCARA_LEDS;
    LATB = 0;
    LATC = ~0;
    
    InicializarUART_RX();
}

void RECEPCION(void) {
    
    InicializarUART_RX();
    
    while(1) {
        while(U1STAbits.URXDA == 0);
        LATCCLR = U1RXREG & MASCARA_LEDS;
    }
}
