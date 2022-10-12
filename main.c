#include "app/app.h"
#include "ecu/led.h"
#include "mcal/gpio.h"
#include "mcal/interrupt.h"
#include "mcal/timer.h"

int main(void)
{
  // TODO[] declare a function poointer that will be assigned a transition
  // funciton in timer ISR
  // TODO[] while in super loop, check if that pointer is not null, execute
  // transition
  // TODO[] reset that pointer to null once transition is complete.
  /// TODO[] consider FSM for light switch
  init_GPIO();
  init_timer();
  init_interrupt();
  app_start();
  return 0;
}
