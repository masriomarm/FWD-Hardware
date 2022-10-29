/******************************************************************************
* File:             main.c
*
* Author:           Omar Elmasri
* Created:          10/28/22
* Description:      FWD Embedded Systems Professional, ATmega32 hardware prj
*****************************************************************************/

#include "app/app.h"

int main(void)
{
  if(app_start()) error_handle();

  return 0;
}
