#pragma once
#if defined LCD_SCREEN

#include "Config.h"
#include "LiquidCrystal_I2C.h"
#include "Screen.h"

class Screen_lcd : public Screen
{
  public:
  Screen_lcd();
  void display_start() override;
  void display_calib_mode() override;
  void display_save_data() override;
  void display_ph(const float temperature, const float ph) override;
  void display_ec(const float temperature, const float ec) override;
  void display_calibration_ph(const uint8_t sample, const float temperature) override;
  void display_calibration_ec(const double sample, uint8_t position, const float temperature) override;

  private:
  LiquidCrystal_I2C m_display;
};
#endif