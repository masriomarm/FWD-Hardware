#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <util/delay.h>

#define SWT_PEDS       INT0
#define TRANS_DURATION 1000

uint8_t init_timer(void)
{
  /// set prescaler to 1024
  /// init timer2 to fire at 5000ms
  /// enable timer interrupt.

  TCCR1B |= (0b101 << 0); /// 1024 prescaler. 0b101
  TCCR1B &= ~(1 << 1);    /// 1024 prescaler. 0b101

  uint16_t cnt = (TRANS_DURATION) /
                 (F_CPU / (1024.0 * 1000)); /// at 1024 prescaler & clk 1MHz.
  OCR1B = (uint16_t)cnt - 1;
  TIMSK |= (1 << OCIE1B);

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
}

ISR(TIMER1_COMPB_vect)
{
  /// reset timer1 counter
  /// set transition flag
  PORTA ^= LED_CARS_GRN | LED_CARS_RED | LED_CARS_YEL;
  TCNT1 = 0;
}

int main(void)
{
  init_GPIO();
  init_timer();
  while (1)
    ;
}
