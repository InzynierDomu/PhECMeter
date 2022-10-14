/**
 * @file Screen_lcd.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief 16x2 lcd Screen
 * @date 2022-08
 */
#pragma once
#if defined LCD_SCREEN

#include "Config.h"
#include "IScreen.h"
#include "LiquidCrystal_I2C.h"

class Screen_lcd : public IScreen
{
  public:
  Screen_lcd();
  void display_start() override;
  void display_calib_mode() override;
  void display_range_mode() override;
  void display_save_data() override;
  void display_ph(const float temperature, const float ph) override;
  void display_ec(const float temperature, const float ec) override;
  void display_calibration_ph(const uint8_t sample, const float temperature) override;
  void display_calibration_ec(const double sample, uint8_t position, const float temperature) override;
  void display_change_ph_range(const double value, uint8_t position);
  void display_change_ec_range(const double value, uint8_t position);
  void display_fill_ph();
  void display_fill_ec();

  private:
  LiquidCrystal_I2C m_display; ///< HD44780 via PCF8574
};
#endif