/* 
 * File:   temp.h
 * Author: Emili
 *
 * Created on 17 de febrero de 2022, 17:22
 */

#ifndef TEMP_H
#define	TEMP_H
#include <stdint.h> // Define uint32_t

void InicializarTimer(void);
uint32_t TicksDesdeArr(void);
void resetTicks(void);
uint32_t setCount(void);
#endif	/* TEMP_H */
