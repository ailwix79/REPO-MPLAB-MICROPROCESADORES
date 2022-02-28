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

void InicializarUART_DUAL(void) {
    U1BRG = 32;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 1;
    U1RXR = 3;
    SYSKEY = 0x11112222;
    
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
    InicializarTarjeta_DUAL();
    
    puls_ant = (PORTB >> 5) & 1;
    
    while(1) {
        puls_act = (PORTB >> 5) & 1;
        
        // ESTRUCTURA ESTILO FIRE AND FORGET
        
        if ((puls_ant != puls_act) && (puls_act == 0)) {
            
            U1STAbits.UTXEN = 1;
            
            while(*pc != '\0') {
                U1TXREG = *pc;
                while (U1STAbits.TRMT == 0);
                pc++;
            }
            
            pc = caracter;
            U1STAbits.UTXEN = 0;
        }
        
        puls_ant = puls_act;
        
        if (U1STAbits.URXDA == 1) {
            LATC = ~(U1RXREG & MASCARA_LEDS);
        }
    }
}


