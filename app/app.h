#ifndef APP_H_YIBHFNWS
#define APP_H_YIBHFNWS

#include "../ecual/led/led.h"
#include "../mcal/gpio/gpio.h"
#include "../mcal/interrupt/interrupt.h"
#include "../mcal/timer/timer.h"
#include "../mcal/uart/uart.h"
#include <stdlib.h>
#include <string.h>


#define STATE_FIRST EN_GRN
#define STATE_LAST  EN_RED

typedef enum { EN_GRN, EN_YEL, EN_RED } EN_LIGHT_t;
typedef enum { EN_CARS, EN_PEDS } EN_MODE_t;

extern EN_LIGHT_t sig_cars;
extern EN_MODE_t  en_mode;

uint8_t app_start(void);
void    error_handle(void);

#endif /* end of include guard: APP_H_YIBHFNWS */
