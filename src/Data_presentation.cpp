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
void Data_presentation::calibration_mode()
{
  m_display.calibration_mode();
  delay(500);
}

/**
 * @brief save point info screen
 */
void Data_presentation::save_data()
{
  m_display.save_data();
  delay(500);
}

/**
 * @brief send ph and temperature and print on screen
 * @param temperature: temperature value to send and print
 * @param ph: ph value to send and print
 */
void Data_presentation::measurements_ph(const float temperature, const float ph)
{
  Serial.print("temperature:");
  Serial.print(temperature);
  // TODO: add unit
  Serial.print(";pH:");
  Serial.println(ph);
  m_display.measurements_ph(temperature, ph);
}

/**
 * @brief send ec and temperature and print on screen
 * @param temperature: temperature value to send and print
 * @param ph: ec value to send and print
 */
void Data_presentation::measurements_ec(const float temperature, const float ec)
{
  Serial.print("temperature:");
  Serial.print(temperature);
  // TODO: add unit
  Serial.print(";EC:");
  Serial.println(ec);

  m_display.measurements_ec(temperature, ec);
}

/**
 * @brief ph calibration screen
 * @param sample: ph value current calibrating
 * @param temperature: current temperature
 * @param origin: //TODO:
 */
void Data_presentation::calibration_ph(const uint8_t sample, const float temperature, const float origin)
{
  m_display.calibration_ph(sample, temperature);
  Serial.println(origin);
}

/**
 * @brief ec calibration screen
 * @param sample: ec value current calibrating
 * @param position: toggling digit position
 * @param temperature: current temperature
 * @param origin: //TODO:
 */
void Data_presentation::calibration_ec(const double sample, uint8_t position, const float temperature, const float origin)
{
  m_display.calibration_ec(sample, position, temperature);
  Serial.println(origin);
}

void Data_presentation::print_ph_calibration(Point points[2])
{
  Serial.print("pH :");
  print_points(points);
}

void Data_presentation::print_ec_calibration(Point points[2])
{
  Serial.print("EC :");
  print_points(points);
}

void Data_presentation::print_points(Point points[2])
{
  Serial.print("analog_val 1:");
  Serial.print(points[0].analog_val);
  Serial.print(" unit_val 1:");
  Serial.print(points[0].unit_val);
  Serial.print(" analog_val 2:");
  Serial.print(points[1].analog_val);
  Serial.print(" unit_val 2:");
  Serial.println(points[1].unit_val);
}