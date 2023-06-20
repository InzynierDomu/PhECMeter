/**
 * @file Sd_card.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief sd card handling
 * @date 2022-08
 */
#include "Sd_card.h"

#include "Config.h"

/**
 * @brief Construct a new Sd_card::Sd_card object
 */
Sd_card::Sd_card()
: m_card_available(false)
{}

/**
 * @brief check is sd card available and begin communication
 * @return is sd card available
 */
bool Sd_card::is_card_available()
{
  if (!m_card_available)
  {
    if (SD.begin(Config::sd_card_cs_pin))
    {
      m_card_available = true;
      return true;
    }
  }
  return false;
}

/**
 * @brief get is sd card available
 * @return is sd card available
 */
bool Sd_card::get_card_status()
{
  return m_card_available;
}

/**
 * @brief save ph measurement on sd
 * @param temperature actual temperature to save
 * @param ph actual ph value to save
 */
void Sd_card::save_ph_measurement(const float temperature, const float ph)
{
  String measurement = "Temperature:";
  measurement += String(temperature);
  measurement += "°C pH:";
  measurement += String(ph);
  save_measurement(measurement);
}

/**
 * @brief save ec measurement on sd
 * @param temperature actual temperature to save
 * @param ec actual ec value to save
 */
void Sd_card::save_ec_measurement(const float temperature, const float ec)
{
  String measurement = "Temperature:";
  measurement += String(temperature);
  measurement += "°C EC:";
  measurement += String(ec);
  measurement += "ms/cm";
  save_measurement(measurement);
}

void Sd_card::print_ph_calibration(Point points[2])
{
  String calibration = "pH calibration: ";
  print_calibration(points, calibration);
  save_measurement(calibration);
}

void Sd_card::print_ec_calibration(Point points[2])
{
  String calibration = "EC calibration: ";
  print_calibration(points, calibration);
  save_measurement(calibration);
}

void Sd_card::print_calibration(Point points[2], String& output)
{
  output += " analog_val 1:";
  output += String(points[0].analog_val);
  output += " unit_val 1:";
  output += String(points[0].unit_val);
  output += " analog_val 2:";
  output += String(points[1].analog_val);
  output += " unit_val 2:";
  output += String(points[1].unit_val);
}

void Sd_card::save_measurement(String& measurement)
{
  if (m_card_available)
  {
    File dataFile = SD.open(Config::file_name, FILE_WRITE);
    if (dataFile)
    {
      dataFile.println(measurement);
      dataFile.close();
    }
    else
    {
      Serial.println("problem with create log file");
    }
  }
}