#include "interrupt.h"

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
