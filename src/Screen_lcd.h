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
  void calibration_mode() override;
  void save_data() override;
  void measurements_ph(const float temperature, const float ph) override;
  void measurements_ec(const float temperature, const float ec) override;
  void calibration_ph(const uint8_t sample, const float temperature) override;
  void calibration_ec(const double sample, uint8_t position, const float temperature) override;

  private:
  LiquidCrystal_I2C m_display; ///< HD44780 via PCF8574
};
#endif