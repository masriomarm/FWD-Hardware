#include "interrupt.h"
#include "../app/app.h"
#include "avr/io.h"
#include "avr/iom32.h"
#include <avr/interrupt.h>

uint8_t tran_time = 0;

void init_interrupt(void)
{
  /// ext0 interrupt
  /// enable global interrupts

  cli();
  GICR |= (1 << SWT_PEDS);      /// enable ext interrupt.
  MCUCR |= (0b10 << 0);         /// interrupt at falling edge.
  sei(); /// enable global interrupt.

}

ISR(TIMER1_COMPB_vect)
{
  /// reset counter val;
  uint8_t sreg = SREG;
  cli();

  tran_time = 1;
  TCNT1 = 0;

  switch (sig_cars)
  {
    case STATE_START:
      tran_ptr = trans_up;
      break;
    case STATE_END:
      tran_ptr = trans_dn;
    default:
      break;
  }

SREG = sreg;
}

ISR(INT0_vect)
{
  /// switch mode, cars or pedstrains.
  if (MCUCR & 1)
  {/// low edge, button pressed
    en_mode = EN_CARS;
    MCUCR &= ~(1 << 0);
  }
  else
  {
    en_mode = EN_PEDS;
    MCUCR |= (1 << 0);
  }
  TCNT1 = 0;
}
