#ifndef GPIO_H_RPHIVENT
#define GPIO_H_RPHIVENT

#include "avr/io.h"
#include "avr/iom32.h"
#include "util/delay.h"

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

void init_GPIO(void);

#endif /* end of include guard: GPIO_H_RPHIVENT */
