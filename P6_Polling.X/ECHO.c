/* 
 * File:   RXTX.c
 * Author: Alejandro
 *
 * Created on 27 de febrero de 2022, 23:22
 */

#include <stdio.h>
#include <stdlib.h>
#include "Pic32Ini.h"
#include "xc.h"

/*
 *  ESCRIBE AQUI EL MENSAJE A ENVIAR, CADA PULSACION ENVÍA UN CARACTER
 */

#define MENSAJE "HOLA MUNDO"

#define PIN_PULSADOR (1<<5)
#define PIN_TX (1<<7)
#define PIN_RX (1<<13)
#define MASCARA_LEDS 15

void InicializarUART_ECHO(void) {
    U1BRG = 32;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1;
    U1RXR = 3;
    SYSKEY = 0x11112222;
    
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;
}

void InicializarTarjeta_ECHO(void) {
    
    ANSELBCLR = PIN_TX | PIN_RX | PIN_PULSADOR;
    ANSELCCLR = MASCARA_LEDS;
    TRISBCLR = PIN_TX;
    TRISBSET = PIN_PULSADOR | PIN_RX;
    TRISCCLR = MASCARA_LEDS;
    LATB = 0;
    LATC = ~0;
    
    InicializarUART_ECHO();
}

void ECHO(void) {

    InicializarTarjeta_ECHO();
   
    while(1) {
        while(U1STAbits.URXDA == 0);
        U1STAbits.UTXEN = 1;    
        U1TXREG = U1RXREG;
        while (U1STAbits.TRMT == 0);
        U1STAbits.UTXEN = 0;
    }
}
