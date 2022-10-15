#include "app/app.h"
#include "ecu/led.h"
#include "mcal/gpio.h"
#include "mcal/interrupt.h"
#include "mcal/timer.h"
#include "util/delay.h"

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
  /*state_grn();*/
  /*_delay_ms(1000);*/
  /*LED_ALL_CLR;*/
  /*state_red();*/
  /*_delay_ms(1000);*/
  /*LED_ALL_CLR;*/
  /*state_yel();*/
  /*_delay_ms(1000);*/
  /*LED_ALL_CLR;*/
  return 0;
}
