/**
 * @file Buttons.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief buttons handling
 * @date 2022-08
 */

#pragma once

#include <Arduino.h>

///< possible recognizing buttons action
enum class Buttons_action
{
  nothing,
  center_pressed,
  up_pressed,
  down_pressed,
  left_pressed,
  right_pressed
};

class Buttons
{
  public:
  static Buttons_action check_buttons(bool r_button_pressed, bool l_button_pressed);

  private:
  static bool check_two_buttons_long();
  static bool check_up_botton_long();
};
