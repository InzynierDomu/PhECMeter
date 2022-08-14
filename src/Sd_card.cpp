#include "Sd_card.h"

#include "Config.h"

/**
 * @brief Construct a new Sd_card::Sd_card object
 */
Sd_card::Sd_card()
: m_card_available(false)
{}

/**
 * @brief
 * @return
 */
bool Sd_card::is_card_available()
{
  if (!m_card_available)
  {
    if (!SD.begin(Config::sd_card_cs_pin))
    {
      m_card_available = true;
      return true;
    }
  }
  return false;
}

/**
 * @brief
 * @param temperature
 * @param ph
 */
void Sd_card::save_ph_measurement(const float temperature, const float ph)
{
  String measurement = "ph";
  save_measurement(measurement);
}

/**
 * @brief
 * @param temperature
 * @param ec
 */
void Sd_card::save_ec_measurement(const float temperature, const float ec)
{
  String measurement = "ec";
  save_measurement(measurement);
}

void Sd_card::save_measurement(String& measurement)
{
  if (m_card_available)
  {
    File dataFile = SD.open(Config::file_name, FILE_WRITE);
    if (dataFile)
    {
      dataFile.println();
      dataFile.close();
    }
  }
}