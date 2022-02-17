#include <xc.h>
#include <stdint.h>
#include "temp.h"

void InicializarTimer2(void)
{
    // Configuraci�n del Timer
    TMR2 = 0;
    T2CON = 0;
    IFS0bits.T2IF = 0;
    PR2 = 19530;
    // Se configura la prioridad de la interrupci�n
    IPC2bits.T2IP = 2;
    //Se configura la subprioridad de la interrupci�n
    IPC2bits.T2IS = 0;
    // Se borra el flag de interrupci�n por si estaba pendiente
    IFS0bits.T2IF = 0;
    // y por �ltimo se habilita su interrupci�n
    IEC0bits.T2IE = 1;
    
    T2CON = 0x8070; //Arranca el Timer con prescalado 256
}

static uint32_t ticks = 0; // Per. reloj desde arranque

__attribute__((vector(_TIMER_2_VECTOR),interrupt(IPL2SOFT),nomips16))
void InterrupcionTimer2(void)
{
    // Se borra el flag de interrupci�n para no volver a
    // entrar en esta rutina hasta que se produzca una nueva
    // interrupci�n.
    IFS0bits.T2IF = 0;
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

