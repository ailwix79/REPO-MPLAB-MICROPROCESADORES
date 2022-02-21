#include <xc.h>
#include <stdint.h>
#include "temp.h"

void InicializarTimer(void)
{
    // Configuración del Timer
    TMR5 = 0;
    T5CON = 0;
    IFS0bits.T5IF = 0;
    PR5 = 39060;            // 2 segundos
    // Se configura la prioridad de la interrupción
    IPC5bits.T5IP = 2;
    //Se configura la subprioridad de la interrupción
    IPC5bits.T5IS = 0;
    // Se borra el flag de interrupción por si estaba pendiente
    IFS0bits.T5IF = 0;
    // y por último se habilita su interrupción
    IEC0bits.T5IE = 1;
    
    T5CON = 0x8070; //Arranca el Timer con prescalado 256
}

static uint32_t ticks = 0; // Per. reloj desde arranque

__attribute__((vector(_TIMER_5_VECTOR),interrupt(IPL2SOFT),nomips16))
void InterrupcionTimer(void)
{
    // Se borra el flag de interrupción para no volver a
    // entrar en esta rutina hasta que se produzca una nueva
    // interrupción.
    
    IFS0bits.T5IF = 0;
    ticks ++;
}

uint32_t TicksDesdeArr(void)
{
    uint32_t c_ticks;
    
    asm(" di"); // Evitamos Ley de Murphy
    c_ticks = ticks;
    asm(" ei");
    
    return c_ticks;
}

void resetTicks(void) 
{
    asm(" di");
    ticks = 0;
    asm(" ei");
}

