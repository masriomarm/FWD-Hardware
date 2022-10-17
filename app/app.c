#include "app.h"

EN_LIGHT_t sig_cars = EN_GRN, sig_peds = EN_GRN;
EN_MODE_t  en_mode = EN_CARS;

extern uint8_t tran_time;

void trans_up(void)
{
  ++sig_cars;
}

void trans_dn(void)
{
  --sig_cars;
}

void (*state_action)(void) = state_grn;

void (*tran_ptr)(void) = trans_up;

void state_red(void)
{
  LED_CARS_RED_ON;
  LED_PEDS_GRN_ON;

  LED_CARS_YEL_OFF;
  LED_CARS_GRN_OFF;
  LED_PEDS_RED_OFF;
  LED_PEDS_YEL_OFF;
}

void state_grn(void)
{
  LED_CARS_GRN_ON;
  LED_PEDS_RED_ON;

  LED_CARS_RED_OFF;
  LED_CARS_YEL_OFF;
  LED_PEDS_GRN_OFF;
  LED_PEDS_YEL_OFF;
}

void state_yel(void)
{
  LED_CARS_YEL_TGL;

  LED_CARS_RED_OFF;
  LED_CARS_GRN_OFF;
  LED_PEDS_GRN_OFF;
  LED_PEDS_RED_OFF;

  if (EN_PEDS == en_mode)
  {
    LED_PEDS_YEL_TGL;
    tran_ptr = trans_up;
  }
  else
  {
    LED_PEDS_YEL_OFF;
    LED_PEDS_RED_ON;
  }
}

void set_state(void)
{
  switch (sig_cars)
  {
    case EN_GRN:
      state_action = state_grn;
      break;
    case EN_YEL:
      state_action = state_yel;
      break;
    case EN_RED:
      state_action = state_red;
      break;
    default:
      break;
  }
}

void app_start(void)
{
  while (1)
  {
    if (tran_time)
    {
      tran_ptr();
      set_state();
      tran_time = 0;
    }
    state_action();
    _delay_ms(500);
  }
}

ISR(TIMER1_COMPB_vect)
{
  TCNT1     = 0;
  tran_time = 1;

  switch (sig_cars)
  {
    case STATE_START:
      tran_ptr = trans_up;
      break;
    case STATE_END:
      tran_ptr = trans_dn;
    default:
      break;
  }
}

ISR(INT0_vect)
{
  /// switch mode, cars or pedstrains.
  if (MCUCR & 1)
  { /// low edge, button pressed
    en_mode = EN_CARS;
    MCUCR &= ~(1 << 0);
  }
  else
  {
    en_mode = EN_PEDS;
    MCUCR |= (1 << 0);
  }
  TCNT1 = 0;
}
