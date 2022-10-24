#include "interrupt.h"

volatile uint8_t interrupt_sw_pds = 0;
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
  /// ext0 interrupt at rising edge
  /// enable global interrupts

  GICR |= (1 << SWT_PEDS); /// enable ext interrupt.
  MCUCR |= (0b11 << 0);    /// interrupt at rising edge.
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
  /// Set peds mode flag
  /// Refresh counter duration
  interrupt_sw_pds = 1;
  TCNT1 = 0;
}
