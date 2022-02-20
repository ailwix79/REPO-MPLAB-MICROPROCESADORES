#include <xc.h>
#include <stdint.h>
#include "temp.h"

#define PIN_PULSADOR 5
#define PIN_LED1 1
#define NUM_PULSACIONES 5

int main(void) {
    
    uint32_t count, ticks;
    int puls_act, puls_ant, i;
    
    ANSELB &= ~(1<<PIN_PULSADOR);
    ANSELC &= ~(1<<PIN_LED1);
    
    TRISC = ~(1<<PIN_LED1);       // Poner como salida RC0, RC3, RC2
    TRISB = (1<<PIN_PULSADOR);    // Todos como salidas menos el pulsador
    LATB = 0;
    LATC = ~0;                    // Al principio ningún LED encendido
              
    InicializarTimer();
    count = 0;
    i = 0;
    
    INTCONbits.MVEC = 1;
    asm("   ei");
    
    puls_ant = (PORTB >> PIN_PULSADOR) & 1;
    
    while (1) {
        
        puls_act = (PORTB >> PIN_PULSADOR) & 1;
                
        ticks = TicksDesdeArr();
        
        if ((puls_act != puls_ant) && (puls_act == 0)) {
            count++;
            
            if (count >= NUM_PULSACIONES) {
                asm("   di");
                
                LATCCLR = (1 << PIN_LED1);
                
                T3CON = 0;
                TMR3 = 0;
                IFS0bits.T3IF = 0;
                PR3 = 39060;
                T3CON = 0x8070;
                        
                while(i != 2) {
                    while(IFS0bits.T3IF == 0);
                    i++;
                }
                
                LATCSET = (1 << PIN_LED1);
                
                resetTicks();
                count = 0;
                
                asm("   ei");
            }
            
        }
        
        if(ticks == 1){             // Cuando pasen 2 segundos
            count = setCount();
            resetTicks();
        }
        
        puls_ant = puls_act;
       
    }
}