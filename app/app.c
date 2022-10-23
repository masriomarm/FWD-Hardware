#include "app.h"

EN_LIGHT_t sig_cars, sig_peds;
EN_MODE_t  en_mode;

void (*state_action)(void) = NULL;
void (*tran_ptr)(void)     = NULL;

/**
 * @brief: Increment current state
 *
 * @param: none
 *
 * @return: none
 *
 */
static void trans_up(void)
{
  ++sig_cars;
}

/**
 * @brief: Decrement current state
 *
 * @param: none
 *
 * @return: none
 *
 */
static void trans_dn(void)
{
  --sig_cars;
}

/**
 * @brief: Execute Red state related actions.
 *
 * @param: none
 *
 * @return: none
 *
 */
static void state_red(void)
{
  LED_CARS_RED_ON;
  LED_PEDS_GRN_ON;

  LED_CARS_YEL_OFF;
  LED_CARS_GRN_OFF;
  LED_PEDS_RED_OFF;
  LED_PEDS_YEL_OFF;
}

/**
 * @brief: Execute Green state related actions.
 *
 * @param: none
 *
 * @return: none
 *
 */
static void state_grn(void)
{
  LED_CARS_GRN_ON;
  LED_PEDS_RED_ON;

  LED_CARS_RED_OFF;
  LED_CARS_YEL_OFF;
  LED_PEDS_GRN_OFF;
  LED_PEDS_YEL_OFF;
}

/**
 * @brief: Execute Yellow state related actions.
 *
 * @param: none
 *
 * @return: none
 *
 */
static void state_yel(void)
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

/**
 * @brief: Set state to execute.
 *
 * @param: none
 *
 * @return: none
 *
 */
static void set_state(void)
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

/**
 * @brief: udpate state transition
 *
 * @param: none
 *
 * @return: none
 *
 */
static void tran_update(void)
{
  switch (sig_cars)
  {
    case STATE_FIRST:
      tran_ptr = trans_up;
      break;
    case STATE_LAST:
      tran_ptr = trans_dn;
    default:
      break;
  }
}

/**
 * @brief: update operation mode
 *
 * @param: none
 *
 * @return: none
 *
 */
static void mode_update(void)
{
  if (interrupt_sw_pds)
    en_mode = EN_CARS;
  else
    en_mode = EN_PEDS;
}

/**
 * @brief: init app global var
 *
 * @param: none
 *
 * @return: none
 *
 */
static void app_init(void)
{
  state_action = state_grn;
  tran_ptr     = trans_up;
  en_mode      = EN_CARS;
  sig_cars     = EN_GRN;
  sig_peds     = EN_GRN;
}

/**
 * @brief: Start running app
 *
 * @param: none
 *
 * @return: none
 *
 */
void app_start(void)
{
  init_GPIO();
  init_timer();
  init_interrupt();

  app_init();

  while (1)
  {
    if (tran_time)
    {
      tran_update();
      tran_ptr();
      set_state();
      tran_time = 0;
    }
    if (interrupt_sw_pds)
    {
      mode_update();
    }
    state_action();
    _delay_ms(500);
  }
}
