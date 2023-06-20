/**
 * @file Screen_lcd.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief OLED Screen
 * @date 2022-08
 */
#pragma once
#ifndef LCD_SCREEN

#include "Config.h"
#include "IScreen.h"
#include "ssd1306.h"
#include "ssd1306_console.h"

#include <SPI.h>


class Screen_oled : public IScreen
{
  public:
  Screen_oled();
  void display_start() override;
  void calibration_mode() override;
  void save_data() override;
  void measurements_ph(const float temperature, const float ph) override;
  void measurements_ec(const float temperature, const float ec) override;
  void calibration_ph(const uint8_t sample, const float temperature) override;
  void calibration_ec(const double sample, uint8_t position, const float temperature) override;
};
#endif