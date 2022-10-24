#include "app/app.h"

int main(void)
{
  if(app_start()) error_handle();

  return 0;
}
