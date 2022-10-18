/**
 * @file Sd_card.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief sd card handling
 * @date 2022-08
 */
#pragma once

#include <SD.h>
#include <SPI.h>
#include "Linear_function.h"

class Sd_card
{
  public:
  Sd_card();
  bool is_card_available();
  bool get_card_status();
  void save_ph_measurement(const float temperature, const float ph);
  void save_ec_measurement(const float temperature, const float ec);
  void print_ph_calibration(Point points[2]);
  void print_ec_calibration(Point points[2]);

  private:
  bool m_card_available; ///< is sd card available

  void save_measurement(String& measurement);
};