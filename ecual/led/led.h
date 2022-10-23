#ifndef LED_H_GYX5PBBN
#define LED_H_GYX5PBBN

#include "../../mcal/gpio/gpio.h"
#include <avr/io.h>
#include <avr/iom32.h>

#define LED_CARS_GRN_ON \
  ((LED_CARS_PORT_GRN) |= (LED_CARS_GRN)) ///< Turn cars green led on
#define LED_CARS_YEL_ON \
  ((LED_CARS_PORT_YEL) |= (LED_CARS_YEL)) ///< Turn cars yellow led on
#define LED_CARS_RED_ON \
  ((LED_CARS_PORT_RED) |= (LED_CARS_RED)) ///< Turn cars red led on

#define LED_CARS_GRN_TGL \
  ((LED_CARS_PORT_GRN) ^= (LED_CARS_GRN)) ///< Toggle cars green led
#define LED_CARS_YEL_TGL \
  ((LED_CARS_PORT_YEL) ^= (LED_CARS_YEL)) ///< Toggle cars yellow led
#define LED_CARS_RED_TGL \
  ((LED_CARS_PORT_RED) ^= (LED_CARS_RED)) ///< Toggle cars red led

#define LED_CARS_GRN_OFF \
  ((LED_CARS_PORT_GRN) &= ~(LED_CARS_GRN)) ///< Turn cars green led off
#define LED_CARS_YEL_OFF \
  ((LED_CARS_PORT_YEL) &= ~(LED_CARS_YEL)) ///< Turn cars yellow led off
#define LED_CARS_RED_OFF \
  ((LED_CARS_PORT_RED) &= ~(LED_CARS_RED)) ///< Turn cars red led off

#define LED_PEDS_GRN_ON \
  ((LED_PEDS_PORT_GRN) |= (LED_PEDS_GRN)) ///< Turn peds green led on
#define LED_PEDS_YEL_ON \
  ((LED_PEDS_PORT_YEL) |= (LED_PEDS_YEL)) ///< Turn peds yellow led on
#define LED_PEDS_RED_ON \
  ((LED_PEDS_PORT_RED) |= (LED_PEDS_RED)) ///< Turn peds red led on

#define LED_PEDS_GRN_TGL \
  ((LED_PEDS_PORT_GRN) ^= (LED_PEDS_GRN)) ///< Toggle peds green led
#define LED_PEDS_YEL_TGL \
  ((LED_PEDS_PORT_YEL) ^= (LED_PEDS_YEL)) ///< Toggle peds yellow led
#define LED_PEDS_RED_TGL \
  ((LED_PEDS_PORT_RED) ^= (LED_PEDS_RED)) ///< Toggle peds red led

#define LED_PEDS_GRN_OFF \
  ((LED_PEDS_PORT_GRN) &= ~(LED_PEDS_GRN)) ///< Turn peds green led off
#define LED_PEDS_YEL_OFF \
  ((LED_PEDS_PORT_YEL) &= ~(LED_PEDS_YEL)) ///< Turn peds yellow led off
#define LED_PEDS_RED_OFF \
  ((LED_PEDS_PORT_RED) &= ~(LED_PEDS_RED)) ///< Turn peds red led off

#endif /* end of include guard: LED_H_GYX5PBBN */
