#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>

#define SWT_PEDS INT0

uint8_t init_interrupt(void)
{
  /// ext0 interrupt at rising edge
  /// enable global interrupts

  GICR |= (1 << SWT_PEDS); /// enable ext interrupt.
  MCUCR |= (0b11 << 0);    /// interrupt at rising edge.
  sei();                   /// enable global interrupt.

  return 0;
}

/** LED definitions **/
#define LED_CARS_PORT_GRN PORTA
#define LED_CARS_PORT_YEL PORTA
#define LED_CARS_PORT_RED PORTA

#define LED_PEDS_PORT_GRN PORTB
#define LED_PEDS_PORT_YEL PORTB
#define LED_PEDS_PORT_RED PORTB

#define LED_CARS_GRN (1 << 0)
#define LED_CARS_YEL (1 << 1)
#define LED_CARS_RED (1 << 2)

#define LED_PEDS_GRN (1 << 0)
#define LED_PEDS_YEL (1 << 1)
#define LED_PEDS_RED (1 << 2)
/** LED definitions **/

void init_GPIO(void)
{
  /// init PA0, PA1, PA2 as output. according to led.
  /// init PB0, PB1, PB2 as output. according to led.
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

ISR(INT0_vect)
{
  /// Set peds mode flag
  /// Refresh counter duration
  PORTA ^= LED_CARS_GRN | LED_CARS_RED | LED_CARS_YEL;
  TCNT1 = 0;
}

int main(void)
{
  init_GPIO();
  init_interrupt();
  while (1)
    ;
}
