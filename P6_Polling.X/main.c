/* 
 * File:   main.c
 * Author: Alejandro
 *
 * Created on 27 de febrero de 2022, 23:59
 */

#include <stdio.h>
#include <stdlib.h>
#include "RX.h"
#include "TX.h"
#include "RXTX.h"

/*
 *  SELECTOR DE EJERCICIO
 */
int main(int argc, char** argv) {
    
    int sel = 1;
    
    if (sel == 1) {
        RECEPCION();
    } else if (sel == 2) {
        TRANSMISION();
    } else {
        TRANSMISION_Y_RECEPCION();
    }
    return (EXIT_SUCCESS);
}

