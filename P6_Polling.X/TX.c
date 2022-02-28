/* 
 * File:   TX.c
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

void InicializarUART_TX(void) {
    U1BRG = 32;
    
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    RPB7R = 3;
    SYSKEY = 0x11112222;
    
    U1STAbits.UTXEN = 1;
    U1MODEbits.ON = 1;
}

void InicializarTarjeta_TX(void) {
    
    ANSELBCLR = PIN_TX | PIN_PULSADOR;
    TRISBCLR = PIN_TX;
    TRISBSET = PIN_PULSADOR;
    TRISC = 0;
    LATB = 0;
    LATC = ~0;
    
    InicializarUART_TX();
}

void TRANSMISION(void) {
    
    
    int puls_act, puls_ant;
    char caracter[] = MENSAJE;
    char *pc;
    
    InicializarUART_TX();
    
    pc = caracter;
    
    puls_ant = (PORTB & PIN_PULSADOR);
    
    while(1) {
        puls_act = (PORTB & PIN_PULSADOR);
        
        // ESTRUCTURA ESTILO FIRE AND FORGET
        
        if (puls_ant != puls_act && puls_act == 0) {
            while (U1STAbits.TRMT == 0);
            U1TXREG = *pc;
            pc++;
        }
        
        // ESTRUCTURA DE MAYOR CONTROL
        
        /*
        if (puls_ant != puls_act && puls_act == 0) {
            if (U1STAbits.TRMT == 1) {
                U1TXREG = *pc;
                pc++;
            }
        }
        */
    }
}


