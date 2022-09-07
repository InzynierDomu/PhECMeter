/**
 * @file main.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief pH and EC meter
 * @date 2022-06
 */

#include "Buttons.h"
#include "Calibration_data_memory.h"
#include "Config.h"
#include "DS18B20.h"
#include "Data_presentation.h"
#include "Linear_function.h"
#include "OneWire.h"

#include <Arduino.h>
#include <EEPROM.h>
#include <math.h>

///< possible device state
enum class Device_state
{
  startup,
  display_measure_ph,
  display_measure_ec,
  calibration_ph,
  calibration_ec
};

byte m_ds_address[8]; ///< ds18b20 thermometer one wire address
OneWire m_one_wire = OneWire(Config::pin_thermometer); ///< one wire bus
DS18B20 m_ds_sensor = DS18B20(Config::pin_thermometer); ///< ds18b20 thermometer
Data_presentation m_data_presentation; ///< screen and serial handling
Calibration_data_memory m_memory; ///< memory handling

Device_state m_device_state = Device_state::startup; ///< actual device state

volatile bool m_up_button_pressed = false; ///< right button pressed flag
volatile bool m_dwn_button_pressed = false; ///< left button pressed flag
Linear_function ph_probe_characteristic; ///< ph probe linear characteristic
Linear_function ec_probe_characteristic; ///< ec probe linear characteristic

/**
 * @brief find thermometer on one wire
 */
void ds_thermometer_init()
{
  m_one_wire.reset_search();
  while (m_one_wire.search(m_ds_address))
  {
    if (m_ds_address[0] != 0x28)
      continue;

    if (OneWire::crc8(m_ds_address, 7) != m_ds_address[7])
    {
      break;
    }
  }
}

/**
 * @brief right button press interrupt
 */
void button_r_pressed()
{
  m_up_button_pressed = true;
}

/**
 * @brief left button press interrupt
 */
void button_l_pressed()
{
  m_dwn_button_pressed = true;
}

/**
 * @brief ph measure
 * @param action: buttons action
 */
void measurements_ph(const Buttons_action action)
{
  float temperature = m_ds_sensor.getTempC();
  int analog_mes = analogRead(Config::ph_pin_probe);
  float ph = ph_probe_characteristic.find_y(analog_mes);

  m_data_presentation.presentation_measurements_ph(temperature, ph);

  switch (action)
  {
    case Buttons_action::two_buttons_long:
      m_data_presentation.display_calib_mode();
      m_device_state = Device_state::calibration_ph;
      break;
    case Buttons_action::up_button_long:
      digitalWrite(Config::ph_supply_pin_probe, LOW);
      digitalWrite(Config::ec_supply_pin_probe, HIGH);
      m_device_state = Device_state::display_measure_ec;
      break;
    default:
      m_device_state = Device_state::display_measure_ph;
      break;
  }
}

/**
 * @brief ec measure
 * @param action: buttons action
 */
void measurements_ec(const Buttons_action action)
{
  float temperature = m_ds_sensor.getTempC();
  int analog_mes = analogRead(Config::ec_pin_probe);
  float ec = ec_probe_characteristic.find_y(analog_mes);

  m_data_presentation.presentation_measurements_ec(temperature, ec);

  switch (action)
  {
    case Buttons_action::two_buttons_long:
      m_data_presentation.display_calib_mode();
      m_device_state = Device_state::calibration_ec;
      break;
    case Buttons_action::up_button_long:
      digitalWrite(Config::ec_supply_pin_probe, LOW);
      digitalWrite(Config::ph_supply_pin_probe, HIGH);
      m_device_state = Device_state::display_measure_ph;
      break;
    default:
      m_device_state = Device_state::display_measure_ec;
      break;
  }
}

/**
 * @brief saving next point in characteristic
 * @param samples points to characteristic
 * @param sample new reference value
 * @return is calibration finished
 */
bool save_sample(Point* samples, double sample)
{
  static int sample_counter = 0;
  samples[sample_counter].x = sample;
  switch (m_device_state)
  {
    case Device_state::calibration_ph:
      samples[sample_counter].y = analogRead(Config::ph_pin_probe);
      break;
    case Device_state::calibration_ec:
      samples[sample_counter].y = analogRead(Config::ec_pin_probe);
      break;
    default:
      break;
  }

  if (++sample_counter == 2)
  {
    sample_counter = 0;
    return true;
  }
  return false;
}

/**
 * @brief calibration ph procedure
 * @param action buttons action
 */
void calibration_ph(const Buttons_action action)
{
  static uint8_t sample = 4;

  static Point samples[2] = {};

  float temperature = m_ds_sensor.getTempC();

  switch (action)
  {
    case Buttons_action::two_buttons_long:
      m_data_presentation.display_save_data();
      if (save_sample(samples, sample))
      {
        m_memory.save_ph_calibration(samples);
        ph_probe_characteristic.set_points(samples);
        m_device_state = Device_state::display_measure_ph;
      }
      break;
    case Buttons_action::short_dwn_button:
      if (sample > 1)
      {
        sample--;
      }
      break;
    case Buttons_action::short_up_button:
      if (sample < Config::max_ph_to_calib)
      {
        sample++;
      }
      break;
    default:
      m_data_presentation.display_calibration_ph(sample, temperature);
      break;
  }
}

/**
 * @brief calibration ec procedure
 * @param action buttons action
 */
void calibration_ec(const Buttons_action action)
{
  static double sample = 4.0;
  static uint8_t position = 0;

  static Point samples[2] = {};

  float temperature = m_ds_sensor.getTempC();

  switch (action)
  {
    case Buttons_action::two_buttons_long:
      m_data_presentation.display_save_data();
      if (save_sample(samples, sample))
      {
        m_memory.save_ec_calibration(samples);
        ec_probe_characteristic.set_points(samples);
        m_device_state = Device_state::display_measure_ec;
      }
      break;
    case Buttons_action::short_dwn_button:
      sample = sample - pow(10.0, position * (-1.0));
      break;
    case Buttons_action::short_up_button:
      if (sample < Config::max_ec_to_calib)
      {
        sample = sample + pow(10.0, position * (-1.0));
      }
      break;
    case Buttons_action::up_button_long:
      if (position < 3)
      {
        position++;
      }
      else
      {
        position = 0;
      }
      break;
    default:
      m_data_presentation.display_calibration_ec(sample, position, temperature);
      break;
  }
}

/**
 * @brief setup on startup
 */
void setup()
{
  m_data_presentation.init();
  ds_thermometer_init();

  Point points[2];
  m_memory.load_ph_calibration(points);
  ph_probe_characteristic.set_points(points);
  m_memory.load_ec_calibration(points);
  ec_probe_characteristic.set_points(points);

  pinMode(Config::ph_supply_pin_probe, OUTPUT);
  digitalWrite(Config::ph_supply_pin_probe, HIGH);
  pinMode(Config::ec_supply_pin_probe, OUTPUT);
  digitalWrite(Config::ec_supply_pin_probe, LOW);
  pinMode(Config::pin_up_button, INPUT_PULLUP);
  pinMode(Config::pin_dwn_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Config::pin_up_button), button_r_pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(Config::pin_dwn_button), button_l_pressed, FALLING);

  m_device_state = Device_state::display_measure_ph;
}

/**
 * @brief main loop with state machine
 */
void loop()
{
  Buttons_action action = Buttons_action::nothing;
  if (m_up_button_pressed || m_dwn_button_pressed)
  {
    action = Buttons::check_buttons(m_up_button_pressed, m_dwn_button_pressed);
    if (action != Buttons_action::nothing)
    {
      m_up_button_pressed = false;
      m_dwn_button_pressed = false;
      delay(100);
    }
  }

  switch (m_device_state)
  {
    case Device_state::display_measure_ph:
      measurements_ph(action);
      break;
    case Device_state::display_measure_ec:
      measurements_ec(action);
      break;
    case Device_state::calibration_ph:
      calibration_ph(action);
      break;
    case Device_state::calibration_ec:
      calibration_ec(action);
      break;
    default:
      break;
  }
}