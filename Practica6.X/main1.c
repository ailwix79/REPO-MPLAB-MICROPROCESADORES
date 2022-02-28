/* 
 * File:   main1.c
 * Author: Alejandro
 *
 * Created on 24 de febrero de 2022, 9:20
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funRX.h"

/*
 *  PRACTICA 6 COMUNICACIÓN BLUETOOTH
 */

#define MASCARA_LEDS 15

int main1(int argc, char** argv) {
    
    char rx = '\0';
    
    ANSELCCLR = MASCARA_LEDS;
    TRISCCLR = MASCARA_LEDS;
    LATCSET = MASCARA_LEDS;
    
    InicializarUART_RX();
    asm("   ei");
        
    while(1) {
        rx = getRX();
        
        if (rx != '\0') {
            LATC = ~(rx & MASCARA_LEDS);
        }
    }

    return (EXIT_SUCCESS);
}

