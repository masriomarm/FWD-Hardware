#include "app.h"

typedef enum { EN_GRN, EN_YEL, EN_RED } EN_LIGHT_t;
EN_LIGHT_t sig_cars = EN_RED, sig_peds = EN_RED;
typedef enum { EN_CARS, EN_PEDS } EN_MODE_t;
EN_MODE_t en_mode = EN_CARS;
uint8_t   mode    = 0;

void (*state)(void);
void state_red(void);
void state_grn(void);
void state_yel(void);
void state_red(void)
{
  switch (en_mode)
  {
    case EN_CARS:
      switch (sig_cars)
      {
        case EN_RED:
          LED_CARS_RED_ON;
          LED_CARS_GRN_OFF;
          LED_CARS_YEL_OFF;
          LED_PEDS_GRN_OFF;
          LED_PEDS_RED_OFF;
          LED_PEDS_YEL_OFF;
          break;
        case EN_YEL:
          LED_CARS_YEL_TGL;
          LED_CARS_GRN_OFF;
          LED_CARS_RED_OFF;
          LED_PEDS_GRN_OFF;
          LED_PEDS_RED_OFF;
          LED_PEDS_YEL_OFF;
          break;
        case EN_GRN:
          LED_CARS_GRN_ON;
          LED_CARS_YEL_OFF;
          LED_CARS_RED_OFF;
          LED_PEDS_GRN_OFF;
          LED_PEDS_RED_OFF;
          LED_PEDS_YEL_OFF;
          break;
        default:
          break;
      }
      break;
    case EN_PEDS:
      switch (sig_cars)
      {
        case EN_RED:
          LED_PEDS_GRN_ON;
          LED_PEDS_RED_OFF;
          LED_CARS_YEL_OFF;
          break;
        case EN_YEL:
          LED_CARS_YEL_TGL;
          LED_CARS_GRN_OFF;
          LED_CARS_RED_OFF;
          break;
        case EN_GRN:
          LED_CARS_YEL_TGL;
          LED_CARS_YEL_OFF;
          LED_CARS_RED_OFF;
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
void (*tran_ptr)(void) = NULL;
void app_start(void)
{
  while (1)
  {
    if (tran_ptr)
    {
      tran_ptr();
    }
  }
}
void transition_cars(void)
{
  /// switch current state & apply transition accordingly.
  /// reset funcptr to NULL;
  switch (sig_cars)
  {
    case EN_GRN:
      sig_cars = EN_YEL;
      break;
    case EN_RED:
      sig_cars = EN_GRN;
      break;
    case EN_YEL:
      sig_cars = EN_RED;
      break;
  }
  tran_ptr = NULL;
}
void transition_pedstrain(void)
{
  /// switch current state & apply transition accordingly.
  /// reset funcptr to NULL;
  switch (sig_peds)
  {
    case EN_GRN:
      sig_cars = EN_YEL;
      break;
    case EN_RED:
      sig_cars = EN_GRN;
      break;
    case EN_YEL:
      sig_cars = EN_RED;
      break;
  }
  tran_ptr = NULL;
}
