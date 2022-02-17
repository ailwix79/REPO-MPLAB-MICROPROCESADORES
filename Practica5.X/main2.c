#include <xc.h>
#include <stdint.h>

#define PIN_PULSADOR 5
#define PIN_LED3 3
#define PIN_LED2 2
#define T_PARPADEO_T2 0 // en ms
#define T_PARPADEO_T3 0 // en ms

#include "temp2.h"
#include "temp3.h"

int main(void)
{
    uint32_t ticks2_ant, ticks3_ant, ticks2_act, ticks3_act;
    int pulsador;
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= ~15;
    
    TRISC = ~13;                   // Poner como salida RC0, RC3, RC2
    TRISB = (1<<PIN_PULSADOR);    // Todos como salidas menos el pulsador
    LATB = 0;
    LATC = 0xFFFF;                // Al principio ningún LED encendido
              
    InicializarTimer2();
    InicializarTimer3();
    
    //Una vez inicializados los periféricos, activamos
    // las interrupciones
    INTCONbits.MVEC = 1; // Modo multivector
    asm(" ei");
    ticks2_ant = Ticks2DesdeArr();
    ticks3_ant = Ticks3DesdeArr();
    
    while (1) {
        // Se lee el estado del pulsador
        pulsador = (PORTB >> PIN_PULSADOR) & 1;
        
        ticks2_act = Ticks2DesdeArr();
        if((ticks2_act-ticks2_ant) > T_PARPADEO_T2){
            ticks2_ant = ticks2_act;
            LATCINV = 1 << PIN_LED3;
        }
        
        ticks3_act = Ticks3DesdeArr();
        if((ticks3_act-ticks3_ant) > T_PARPADEO_T3){
            ticks3_ant = ticks3_act;
            LATCINV = 1 << PIN_LED2;
        }
        
        if (pulsador == 0) {
            LATC &= ~1;
            } else {
            LATC |= 1;  
            }
    }
}
