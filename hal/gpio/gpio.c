#include "gpio.h"

void init_GPIO(void)
{
  /// init PA0, PA1, PA2 output. according to led.
  /// init PB0, PB1, PB2 output. according to led.
  DDRA = LED_CARS_GRN | LED_CARS_RED | LED_CARS_YEL;
  DDRB = LED_PEDS_GRN | LED_PEDS_RED | LED_PEDS_YEL;

  PORTA |= LED_CARS_GRN | LED_CARS_RED | LED_CARS_YEL;
  _delay_ms(1000);
  PORTA ^= LED_CARS_GRN | LED_CARS_RED | LED_CARS_YEL;

  _delay_ms(100);

  PORTB |= LED_PEDS_GRN | LED_PEDS_RED | LED_PEDS_YEL;
  _delay_ms(1000);
  PORTB ^= LED_PEDS_GRN | LED_PEDS_RED | LED_PEDS_YEL;

  _delay_ms(100);
}
