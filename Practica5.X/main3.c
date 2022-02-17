#include <xc.h>
#include <stdint.h>

#define PIN_PULSADOR 5
#define PIN_LED3 3
#define PIN_LED2 2
#define T_PARPADEO_T2 0 // en ms
#define T_PARPADEO_T3 0 // en ms

#include "temp2.h"

int main3(void)
{
    uint32_t count, ticks_ant, ticks_act;
    int puls_act, puls_ant;
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= 0;
    
    TRISC = 0;                   // Poner como salida RC0, RC3, RC2
    TRISB = (1<<PIN_PULSADOR);    // Todos como salidas menos el pulsador
    LATB = 0;
    LATC = 0xFFFF;                // Al principio ningún LED encendido
              
    InicializarTimer2();
    count = 0;
    
    //Una vez inicializados los periféricos, activamos
    // las interrupciones
    INTCONbits.MVEC = 1; // Modo multivector
    asm(" ei");
    ticks_ant = Ticks2DesdeArr();
    
    puls_ant = (PORTB >> PIN_PULSADOR) & 1;
    while (1) {
        // Se lee el estado del pulsador
        puls_act = (PORTB >> PIN_PULSADOR) & 1;
        
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            count++;
        }
        ticks_act = Ticks2DesdeArr();
        if((ticks_act-ticks_ant) > T_PARPADEO_T2){
            ticks_ant = ticks_act;
            LATCINV = 1 << PIN_LED3;
        }
        puls_ant = puls_act;
       
    }
}