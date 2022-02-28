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
#include "ECHO.h"
#include "Pic32Ini.h"

/*
 *  SELECTOR DE EJERCICIO
 */
int main(int argc, char** argv) {
    //RECEPCION();
    //TRANSMISION();
    //TRANSMISION_Y_RECEPCION();
    ECHO();
    return (EXIT_SUCCESS);
}

