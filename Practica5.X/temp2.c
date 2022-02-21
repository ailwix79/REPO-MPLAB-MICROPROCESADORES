#include <xc.h>
#include <stdint.h>
#include "temp2.h"

void InicializarTimer2(void)
{
    // Configuración del Timer
    TMR2 = 0;
    T2CON = 0;
    IFS0bits.T2IF = 0;
    PR2 = 19530;    // 1 segundo
    // Se configura la prioridad de la interrupción
    IPC2bits.T2IP = 2;
    //Se configura la subprioridad de la interrupción
    IPC2bits.T2IS = 0;
    // Se borra el flag de interrupción por si estaba pendiente
    IFS0bits.T2IF = 0;
    // y por último se habilita su interrupción
    IEC0bits.T2IE = 1;
    
    T2CON = 0x8070; //Arranca el Timer con prescalado 256
}

static uint32_t ticks2 = 0; // Per. reloj desde arranque

__attribute__((vector(_TIMER_2_VECTOR),interrupt(IPL2SOFT),nomips16))
void InterrupcionTimer2(void)
{
    // Se borra el flag de interrupción para no volver a
    // entrar en esta rutina hasta que se produzca una nueva
    // interrupción.
    
    IFS0bits.T2IF = 0;
    ticks2 ++;
}

uint32_t Ticks2DesdeArr(void)
{
    uint32_t c_ticks2;
    
    asm(" di"); // Evitamos Ley de Murphy
    c_ticks2 = ticks2;
    asm(" ei");
    
    return c_ticks2;
}


