#include "timer.h"
#include <avr/io.h>
#include <avr/iom32.h>
#include "avr/interrupt.h"


void init_timer(void)
{
  /// init timer2 to fire at 5000ms
  volatile uint8_t sreg = SREG;
  cli();

  /// operating in CTC
  TCCR1B |= (0b101 << 2); /// 1024 prescaler. 0b101
  TCCR1B &= ~(1 << 1);    /// 1024 prescaler. 0b101
  uint16_t cnt = (TRANS_DURATION ) / (F_CPU / (1024.0 * 1000));
  OCR1B        = (uint16_t)cnt - 1; /// 5000ms at 1024 prescaler & clk 1MHz.
  TIMSK |= (1 << OCIE1B); /// enable timer interrupt.

  SREG = sreg;
}
