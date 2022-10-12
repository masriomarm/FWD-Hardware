#ifndef APP_H_YIBHFNWS
#define APP_H_YIBHFNWS

#include "stdint.h"
#include "stdlib.h"
#include "../ecu/led.h"


extern void (*tran_ptr)(void);

void app_start(void);
void transition_cars(void);
void transition_pedstrain(void);
#endif /* end of include guard: APP_H_YIBHFNWS */
