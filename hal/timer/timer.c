#include "timer.h"

uint8_t tran_time = 0;

/**
* @brief: Init timer 1 configuration for required timing.
*
* @param: none
*
* @return: none
*
*/
void init_timer(void)
{
  /// init timer2 to fire at 5000ms
  /// operating in CTC

  TCCR1B |= (0b101 << 0); /// 1024 prescaler. 0b101
  TCCR1B &= ~(1 << 1);    /// 1024 prescaler. 0b101

  uint16_t cnt = (TRANS_DURATION) /
                 (F_CPU / (1024.0 * 1000)); /// at 1024 prescaler & clk 1MHz.
  OCR1B = (uint16_t)cnt - 1;

  TIMSK |= (1 << OCIE1B); /// enable timer interrupt.
}
