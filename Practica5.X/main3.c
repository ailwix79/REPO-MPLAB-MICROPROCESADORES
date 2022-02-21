#include <xc.h>
#include <stdint.h>
#include "temp.h"

#define PIN_PULSADOR 5
#define PIN_LED_WIN 1
#define NUM_PULSACIONES 5

int main(void) {
    
    uint32_t count, win;
    int puls_act, puls_ant;
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= ~(1<<PIN_LED_WIN);
    
    TRISC = ~(1<<PIN_LED_WIN);       // Poner como salida RC0, RC3, RC2
    TRISB = (1<<PIN_PULSADOR);    // Todos como salidas menos el pulsador
    
    LATB = 0;
    LATC = ~0;                    // Al principio ningún LED encendido
              
    InicializarTimer();
    
    INTCONbits.MVEC = 1;
    asm("   ei");
    
    puls_ant = (PORTB >> PIN_PULSADOR) & 1;
    
    while (1) {
        
        puls_act = (PORTB >> PIN_PULSADOR) & 1;
        
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            if ((LATC >> PIN_LED_WIN) & 1){
                count++;
                if (count >= NUM_PULSACIONES) {
                    LATCCLR = (1<<PIN_LED_WIN);

                    asm("   di");
                    resetTicks();
                    asm("   ei");

                    count = 0;
                    win = 1;
                }
            }
        }

        if ((TicksDesdeArr() == 1) && (win == 0)) {             // Cuando pasen 2 segundos
            count = 0;
            asm("   di");
            resetTicks();
            asm("   ei");
            
        } else if ((TicksDesdeArr() == 2) && (win == 1)) {
            LATCSET = (1<<PIN_LED_WIN);
            win = 0;
            count = 0;
            asm("   di");
            resetTicks();
            asm("   ei");
        }
        
        puls_ant = puls_act;
       
    }
}