/* 
 * File:   main3.c
 * Author: ailwx
 *
 * Created on 24 de febrero de 2022, 10:06
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funTXRX.h"

/*
 * 
 */

#define PIN_PULSADOR 5
#define TAM_MAX 80
#define MASCARA_LEDS 15

int main3(int argc, char** argv) {
    int puls_ant, puls_act;
    static char tx[TAM_MAX] = "HOLA";
    char rx = '\0';
    
    ANSELCCLR = MASCARA_LEDS;
    TRISCCLR = MASCARA_LEDS;
    LATCSET = MASCARA_LEDS;
    
    puls_ant = (PORTB >>PIN_PULSADOR) & 1;
    
    InicializarUART_TX_RX();
    
    asm("   ei");
    
    while(1) {
        puls_act = (PORTB >>PIN_PULSADOR) & 1;
        
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            setTX(tx);
        }
        
        rx = getRX();
        
        if (rx != '\0') {
            LATC = ~(rx & MASCARA_LEDS);
        }
        
        puls_ant = puls_act;
    }
    return (EXIT_SUCCESS);
}
