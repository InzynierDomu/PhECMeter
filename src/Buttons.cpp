#include "Buttons.h"

#include "Config.h"

/**
 * @brief buttons action reaction
 * @return Buttons_action type of action was done
 */
Buttons_action Buttons::check_buttons(bool r_button_pressed, bool l_button_pressed)
{
  // TODO: check button naming

  if (r_button_pressed || l_button_pressed)
  {
    if (check_two_buttons_2s(r_button_pressed, l_button_pressed))
    {
      return Buttons_action::two_buttons_2s;
    }
    if (check_up_botton_2s(r_button_pressed, l_button_pressed))
    {
      return Buttons_action::up_button_2s;
    }
  }

  if (digitalRead(Config::pin_up_button) && digitalRead(Config::pin_dwn_button))
  {
    if (l_button_pressed)
    {
      return Buttons_action::short_dwn_button;
    }
    else if (r_button_pressed)
    {
      return Buttons_action::short_up_button;
    }
  }
  delay(100);
  return Buttons_action::nothig;
}

bool Buttons::check_two_buttons_2s(bool r_button_pressed, bool l_button_pressed)
{
  long buttons_start_press = millis();
  do
  {
    long loop_time = millis();
    if (loop_time - buttons_start_press > Config::long_press_time)
    {
      l_button_pressed = false;
      r_button_pressed = false;
      return true;
    }
  } while (!digitalRead(Config::pin_up_button) && !digitalRead(Config::pin_dwn_button));
  return false;
}

bool Buttons::check_up_botton_2s(bool r_button_pressed, bool l_button_pressed)
{
  long buttons_start_press = millis();
  do
  {
    long loop_time = millis();
    if (loop_time - buttons_start_press > Config::long_press_time)
    {
      l_button_pressed = false;
      r_button_pressed = false;
      return true;
    }
  } while (!digitalRead(Config::pin_up_button) && digitalRead(Config::pin_dwn_button));
  return false;
}