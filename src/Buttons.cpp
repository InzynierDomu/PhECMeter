#include "Buttons.h"

#include "Config.h"

/**
 * @brief buttons action reaction
 * @return Buttons_action type of action was done
 */
Buttons_action Buttons::check_buttons(bool r_button_pressed, bool l_button_pressed)
{
  // TODO: split to few checks
  long m_buttons_start_press;
  if (r_button_pressed || l_button_pressed)
  {
    m_buttons_start_press = millis();

    // two buttons pressed >2s
    do
    {
      long loop_time = millis();
      if (loop_time - m_buttons_start_press > Config::long_press_time)
      {
        l_button_pressed = false;
        r_button_pressed = false;
        return Buttons_action::two_buttons_2s;
      }
    } while (!digitalRead(Config::pin_up_button) && !digitalRead(Config::pin_dwn_button));

    // check up button pressed >2s
    do
    {
      long loop_time = millis();
      if (loop_time - m_buttons_start_press > Config::long_press_time)
      {
        l_button_pressed = false;
        r_button_pressed = false;
        return Buttons_action::up_button_2s;
      }
    } while (!digitalRead(Config::pin_up_button) && digitalRead(Config::pin_dwn_button));
  }

  if (digitalRead(Config::pin_up_button) && digitalRead(Config::pin_dwn_button))
  {
    if (l_button_pressed)
    {
      l_button_pressed = false;
      return Buttons_action::short_dwn_button;
    }
    else if (r_button_pressed)
    {
      r_button_pressed = false;
      return Buttons_action::short_up_button;
    }
  }
  delay(100);
  return Buttons_action::nothig;
}