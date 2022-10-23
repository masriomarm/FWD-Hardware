#include "interrupt.h"

volatile uint8_t interrupt_sw_pds = 1;
volatile uint8_t tran_time        = 0;

/**
 * @brief: Init interrupt configurations.
 *
 * @param: none
 *
 * @return: none
 *
 */
uint8_t init_interrupt(void)
{
  /// ext0 interrupt at falling edge
  /// enable global interrupts

  GICR |= (1 << SWT_PEDS); /// enable ext interrupt.
  MCUCR |= (0b10 << 0);    /// interrupt at falling edge.
  sei();                   /// enable global interrupt.

  return 0;
}

/**
 * @brief: Timer compare channle B interrupt handler
 *
 * @param: none
 *
 * @return: none
 *
 */
ISR(TIMER1_COMPB_vect)
{
  /// reset timer1 counter
  /// set transition flag

  TCNT1     = 0;
  tran_time = 1;
}

/**
 * @brief: Ext_Int0 interrupt handler.
 *
 * @param: none
 *
 * @return: none
 *
 */
ISR(INT0_vect)
{
  /// check for current edge level
  /// take action accordingly and toggle edge level
  /// reset timer1 counter to refresh duration

  if (MCUCR & 1)
  { /// falling edge, button pressed
    interrupt_sw_pds = 0;
    MCUCR &= ~(1 << 0);
  }
  else
  { /// rising edge, button released.
    interrupt_sw_pds = 1;
    MCUCR |= (1 << 0);
  }
  TCNT1 = 0;
}
