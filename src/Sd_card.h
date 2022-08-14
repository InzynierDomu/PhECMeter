#pragma once

#include <SD.h>
#include <SPI.h>

class Sd_card
{
  public:
  Sd_card();
  bool is_card_available();
  void save_ph_measurement(const float temperature, const float ph);
  void save_ec_measurement(const float temperature, const float ec);

  private:
  void save_measurement(String& measurement);
  bool m_card_available;
};