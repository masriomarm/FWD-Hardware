#include "app/app.h"

int main(void)
{
  init_GPIO();
  init_timer();
  init_interrupt();
  app_start();

  return 0;
}
