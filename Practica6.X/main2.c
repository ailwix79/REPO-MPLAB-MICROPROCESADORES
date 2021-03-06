/* 
 * File:   main2.c
 * Author: ailwx
 *
 * Created on 24 de febrero de 2022, 10:06
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc.h"
#include "funTX.h"

/*
 * 
 */
#define PIN_PULSADOR 5
#define TAM_MAX 80

int main2(int argc, char** argv) {
    int puls_ant, puls_act;
    static char tx[TAM_MAX] = "HOLA";
    
    puls_ant = (PORTB >>PIN_PULSADOR) & 1;
    InicializarUART_TX();
    
    asm("   ei");
    
    while(1) {
        puls_act = (PORTB >>PIN_PULSADOR) & 1;
        
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            setTX(tx);
        }
        
        puls_ant = puls_act;
    }
    return (EXIT_SUCCESS);
}

