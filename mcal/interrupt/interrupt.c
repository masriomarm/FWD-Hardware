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
void init_interrupt(void)
{
  /// ext0 interrupt
  /// enable global interrupts

  cli();
  GICR |= (1 << SWT_PEDS); /// enable ext interrupt.
  MCUCR |= (0b10 << 0);    /// interrupt at falling edge.
  sei();                   /// enable global interrupt.
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
  /// switch mode, cars or pedstrains.
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
