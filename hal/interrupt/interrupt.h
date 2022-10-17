#ifndef INTERRUPT_H_MNDYOC2D
#define INTERRUPT_H_MNDYOC2D

#include "avr/io.h"
#include "avr/iom32.h"
#include <avr/interrupt.h>

#define SWT_PEDS INT0

void init_interrupt(void);
#endif /* end of include guard: INTERRUPT_H_MNDYOC2D */
