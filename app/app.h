#ifndef APP_H_YIBHFNWS
#define APP_H_YIBHFNWS

#include "hal/gpio/gpio.h"
#include "hal/interrupt/interrupt.h"
#include "hal/led/led.h"
#include "hal/timer/timer.h"

#define STATE_START EN_GRN
#define STATE_END   EN_RED

typedef enum { EN_GRN, EN_YEL, EN_RED } EN_LIGHT_t;
typedef enum { EN_CARS, EN_PEDS } EN_MODE_t;

extern EN_LIGHT_t sig_cars;
extern EN_MODE_t  en_mode;

extern void (*tran_ptr)(void);

void app_start(void);

void state_red(void);
void state_grn(void);
void state_yel(void);

void trans_up(void);
void trans_dn(void);
#endif /* end of include guard: APP_H_YIBHFNWS */
