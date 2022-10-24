#include "app.h"

EN_LIGHT_t sig_cars, sig_peds;
EN_MODE_t  en_mode;

uint8_t interrupt_sw_pds_clear = 1;

uint8_t (*state_action)(void) = NULL;
uint8_t (*tran_ptr)(void)     = NULL;

void error_handle(void)
{
  /// toggle cars & peds, yellow & red leds as indicaton of error
  LED_CARS_YEL_ON;
  LED_CARS_GRN_ON;
  LED_CARS_RED_ON;
  _delay_ms(100);

  LED_PEDS_YEL_OFF;
  LED_PEDS_GRN_OFF;
  LED_PEDS_RED_OFF;
  _delay_ms(100);
}
/**
 * @brief: Increment current state
 *
 * @param: none
 *
 * @return: 0
 *
 */
static uint8_t trans_up(void)
{
  ++sig_cars;
  return 0;
}

/**
 * @brief: Decrement current state
 *
 * @param: none
 *
 * @return: 0
 *
 */
static uint8_t trans_dn(void)
{
  --sig_cars;
  return 0;
}

/**
 * @brief: Execute Red state related actions.
 *
 * @param: none
 *
 * @return: 0
 *
 */
static uint8_t state_red(void)
{
  /// red light state actions
  /// car red led on
  /// peds green led on
  /// clear transition (update mode)

  LED_CARS_RED_ON;
  LED_PEDS_GRN_ON;

  LED_CARS_YEL_OFF;
  LED_CARS_GRN_OFF;
  LED_PEDS_RED_OFF;
  LED_PEDS_YEL_OFF;

  interrupt_sw_pds_clear = 1;
  return 0;
}

/**
 * @brief: Execute Green state related actions.
 *
 * @param: none
 *
 * @return: 0 on cars mode, 1 on peds mode
 *
 */
static uint8_t state_grn(void)
{
  /// green light state actions
  /// car green led on
  /// peds red led on
  /// if peds switch pressed,
    /// change to peds mode
    /// maintain transition to next yel (don't update mode)

  LED_CARS_GRN_ON;
  LED_PEDS_RED_ON;

  LED_CARS_RED_OFF;
  LED_CARS_YEL_OFF;
  LED_PEDS_GRN_OFF;
  LED_PEDS_YEL_OFF;

  if (interrupt_sw_pds)
  {
    en_mode = EN_PEDS;
    interrupt_sw_pds_clear = 0;
    return 1;
  }
  return 0;
}

/**
 * @brief: Execute Yellow state related actions.
 *
 * @param: none
 *
 * @return: 0
 *
 */
static uint8_t state_yel(void)
{
  /// yellow light state actions
  /// car yellow led toggle
  /// if peds mode,
    /// peds yellow led toggle
    /// set next to red by trans_up
  /// if cars mode,
    /// peds red led on
    /// peds yel led off
  /// clear transition (update mode)

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
    interrupt_sw_pds_clear = 1;
  return 0;
}

/**
 * @brief: Set state to execute.
 *
 * @param: none
 *
 * @return: 0 on success, 1 on fail
 *
 */
static uint8_t set_state(void)
{
  /// set current light action

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
      return 1;
      break;
  }
  return 0;
}

/**
 * @brief: udpate state transition
 *
 * @param: none
 *
 * @return: 0 on fail, 1 on success
 *
 */
static uint8_t tran_update(void)
{
  switch (sig_cars)
  {
    case STATE_FIRST:
      tran_ptr = trans_up;
      break;
    case STATE_LAST:
      tran_ptr = trans_dn;
    default:
      return 1;
      break;
  }
  return 0;
}

/**
 * @brief: update operation mode
 *
 * @param: none
 *
 * @return: 0 on cars mode, 1 on peds mode
 *
 */
static uint8_t mode_update(void)
{
  /// check if pedstrain switched, act accordingly

  if (interrupt_sw_pds)
  {
    en_mode = EN_PEDS;
    return 1;
  }
  else
  {
    en_mode = EN_CARS;
    return 0;
  }
}

/**
 * @brief: init app global var
 *
 * @param: none
 *
 * @return: 0
 *
 */
static uint8_t app_init(void)
{
  /// init app related vars

  state_action = state_grn;
  tran_ptr     = trans_up;
  en_mode      = EN_CARS;
  sig_cars     = EN_GRN;
  sig_peds     = EN_GRN;
  return 0;
}

/**
 * @brief: Start running app
 *
 * @param: none
 *
 * @return: 1 on fail. super loop, shouldn't return.
 *
 */
uint8_t app_start(void)
{
  /// init timer config
  /// init interrupt config
  /// init DIOs
  /// init app global vars

  init_timer();
  init_interrupt();
  init_GPIO();

  app_init();

  while (1)
  {
    if (tran_time)
    {
      if(tran_update()) error_handle();
      tran_ptr();
      if(set_state()) error_handle();
      tran_time = 0;
      if (interrupt_sw_pds_clear)
      {
        interrupt_sw_pds = 0;
        interrupt_sw_pds_clear = 0;
      }

    }
    if (interrupt_sw_pds)
    {
      mode_update();
    }
    state_action();
    _delay_ms(500);
  }
  return 1;
}
