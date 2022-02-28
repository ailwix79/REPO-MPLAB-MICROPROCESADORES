/* 
 * File:   RXTX.c
 * Author: Alejandro
 *
 * Created on 27 de febrero de 2022, 23:22
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"

/*
 *  ESCRIBE AQUI EL MENSAJE A ENVIAR, CADA PULSACION ENVÍA UN CARACTER
 */

#define MENSAJE "HOLA MUNDO"

#define PIN_PULSADOR (1<<5)
#define PIN_TX (1<<7)
#define PIN_RX (1<<13)
#define MASCARA_LEDS 15

void InicializarUART_DUAL(void) {
    U1BRG = 32;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1;
    U1RXR = 3;
    SYSKEY = 0x11112222;
    
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;
}

void InicializarTarjeta_DUAL(void) {
    
    ANSELBCLR = PIN_TX | PIN_RX | PIN_PULSADOR;
    ANSELCCLR = MASCARA_LEDS;
    TRISBCLR = PIN_TX;
    TRISBSET = PIN_PULSADOR | PIN_RX;
    TRISCCLR = MASCARA_LEDS;
    LATB = 0;
    LATC = ~0;
    
    InicializarUART_DUAL();
}

void TRANSMISION_Y_RECEPCION(void) {
    
    int puls_act, puls_ant;
    char caracter[] = MENSAJE;
    char *pc;
    
    pc = caracter;
    
    InicializarUART_DUAL();
    
    puls_ant = (PORTB & PIN_PULSADOR);
    
    while(1) {
        
        puls_act = (PORTB & PIN_PULSADOR);

        if (puls_ant != puls_act && puls_act == 0) {
            if (U1STAbits.TRMT == 1) {
                U1TXREG = *pc;
                pc++;
            }
        }
  
        if (U1STAbits.URXDA == 1) {
            LATCCLR = U1RXREG & MASCARA_LEDS;
        }
    }
}


