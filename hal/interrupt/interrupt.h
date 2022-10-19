#ifndef INTERRUPT_H_MNDYOC2D
#define INTERRUPT_H_MNDYOC2D

#include "avr/io.h"
#include "avr/iom32.h"
#include <avr/interrupt.h>

#define SWT_PEDS INT0

extern volatile uint8_t interrupt_sw_pds;
extern volatile uint8_t tran_time;

void init_interrupt(void);
#endif /* end of include guard: INTERRUPT_H_MNDYOC2D */
