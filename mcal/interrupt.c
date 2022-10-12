#include "interrupt.h"
#include "avr/io.h"
#include "avr/iom32.h"
#include <avr/interrupt.h>
#include "../app/app.h"


void init_interrupt(void)
{
  /// ext0 interrupt
  /// enable global interrupts

  cli();
  GICR |= SWT_PEDS;      /// enable ext interrupt.
  SREG |= (1 << SREG_I); /// enable global interrupt.
  sei();
}
ISR(TIMER1_COMPB_vect)
{
  /// reset counter val;
  uint8_t sreg = SREG;
  cli();
  TCNT1 = 0;

  /// switch current mode & select transtion accordingly.
  /// if mode cars;
  tran_ptr = transition_cars;
  /// else if mode pedstrains
  tran_ptr = transition_pedstrain;

  SREG = sreg;
}
ISR(INT0_vect)
{
  /// switch mode, cars or pedstrains.
}
