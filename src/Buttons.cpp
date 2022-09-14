/**
 * @file Buttons.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief buttons handling
 * @date 2022-08
 */

#include "Buttons.h"

#include "Config.h"

/**
 * @brief buttons action reaction
 * @return Buttons_action type of action was done
 */
Buttons_action Buttons::check_buttons(bool up_button_pressed, bool dwn_button_pressed)
{
  if (up_button_pressed || dwn_button_pressed)
  {
    if (check_two_buttons_long())
    {
      return Buttons_action::center_pressed;
    }
    if (check_up_botton_long())
    {
      return Buttons_action::right_pressed;
    }
  }

  if (digitalRead(Config::pin_up_button) && digitalRead(Config::pin_down_button))
  {
    if (dwn_button_pressed)
    {
      return Buttons_action::down_pressed;
    }
    else if (up_button_pressed)
    {
      return Buttons_action::up_pressed;
    }
  }

  return Buttons_action::nothing;
}

bool Buttons::check_two_buttons_long()
{
  long buttons_start_press = millis();
  do
  {
    long loop_time = millis();
    if (loop_time - buttons_start_press > Config::long_press_time)
    {
      return true;
    }
  } while (!digitalRead(Config::pin_up_button) && !digitalRead(Config::pin_down_button));
  return false;
}

bool Buttons::check_up_botton_long()
{
  long buttons_start_press = millis();
  do
  {
    long loop_time = millis();
    if (loop_time - buttons_start_press > Config::long_press_time)
    {
      return true;
    }
  } while (!digitalRead(Config::pin_up_button) && digitalRead(Config::pin_down_button));
  return false;
}