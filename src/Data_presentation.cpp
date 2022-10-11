/**
 * @file Data_presentation.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief send data via serial and present on screen
 * @date 2022-06
 */
#include "Data_presentation.h"

#include "Config.h"

#include <Arduino.h>
#include <math.h>

/**
 * @brief Construct a new Data_presentation::Data_presentation object
 */
Data_presentation::Data_presentation()
: m_display()
{}

/**
 * @brief startup screen
 */
void Data_presentation::init()
{
  Serial.begin(9600);

  m_display.display_start();
  delay(1000);
}

/**
 * @brief calibration mode info screen
 */
void Data_presentation::display_calib_mode()
{
  m_display.display_calib_mode();
  delay(500);
}

/**
 * @brief change range mode info screen
 */
void Data_presentation::display_range_mode()
{
  m_display.display_range_mode();
  delay(500);
}

/**
 * @brief save point info screen
 */
void Data_presentation::display_save_data()
{
  m_display.display_save_data();
  delay(500);
}

/**
 * @brief send ph and temperature and print on screen
 * @param temperature: temperature value to send and print
 * @param ph: ph value to send and print
 */
void Data_presentation::presentation_measurements_ph(const float temperature, const float ph)
{
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(ph);

  m_display.display_ph(temperature, ph);
}

/**
 * @brief send ec and temperature and print on screen
 * @param temperature: temperature value to send and print
 * @param ph: ec value to send and print
 */
void Data_presentation::presentation_measurements_ec(const float temperature, const float ec)
{
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(ec);

  m_display.display_ec(temperature, ec);
}

/**
 * @brief ph calibration screen
 * @param sample: ph value current calibrating
 * @param temperature: current temperature
 */
void Data_presentation::display_calibration_ph(const uint8_t sample, const float temperature)
{
  m_display.display_calibration_ph(sample, temperature);
}

/**
 * @brief ec calibration screen
 * @param sample: ec value current calibrating
 * @param position: toggling digit position
 * @param temperature: current temperature
 */
void Data_presentation::display_calibration_ec(const double sample, uint8_t position, const float temperature)
{
  m_display.display_calibration_ec(sample, position, temperature);
}

 void Data_presentation::display_change_ph_range(const double sample, uint8_t position)
 {
  m_display.display_change_ph_range(sample, position);
 }