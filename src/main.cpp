#include "Calibration_data_memory.h"
#include "Config.h"
#include "DS18B20.h"
#include "Data_presentation.h"
#include "Linear_function.h"
#include "OneWire.h"

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <EEPROM.h>

enum class Device_state
{
  startup,
  display_measure_ph,
  display_measure_ec,
  calibration_ph,
  calibration_ec
};

enum class Buttons_action
{
  nothig,
  two_buttons_2s,
  right_button_2s,
  short_right_button,
  short_left_button
};

byte m_ds_address[8];
OneWire m_one_wire = OneWire(Config::m_pin_thermometer);
DS18B20 m_ds_sensor = DS18B20(Config::m_pin_thermometer);
Data_presentation m_data_presentation;
Calibration_data_memory m_memory;

Device_state m_device_state = Device_state::startup;

bool m_r_button_pressed = false;
bool m_l_button_pressed = false;
Linear_function probe_characteristic;

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
  m_r_button_pressed = true;
}

/**
 * @brief left button press interrupt
 */
void button_l_pressed()
{
  m_l_button_pressed = true;
}

void measurements_ph(const Buttons_action action)
{
  float temperature = m_ds_sensor.getTempC();
  int analog_mes = analogRead(Config::m_ph_pin_probe);
  float ph = probe_characteristic.find_y(analog_mes);

  m_data_presentation.presentation_measurements_ph(temperature, ph);

  switch (action)
  {
    case Buttons_action::two_buttons_2s:
      m_data_presentation.display_calib_mode();
      m_device_state = Device_state::calibration_ph;
      break;
    case Buttons_action::right_button_2s:
      digitalWrite(Config::m_ph_supply_pin_probe, LOW);
      digitalWrite(Config::m_ec_supply_pin_probe, HIGH);
      m_device_state = Device_state::display_measure_ec;
      break;
    default:
      m_device_state = Device_state::display_measure_ph;
      break;
  }
}

void measurements_ec(const Buttons_action action)
{
  float temperature = m_ds_sensor.getTempC();
  // TODO: change measure to ec pin and characteristic from ec
  int analog_mes = analogRead(Config::m_ph_pin_probe);
  float ec = probe_characteristic.find_y(analog_mes);

  m_data_presentation.presentation_measurements_ec(temperature, ec);

  switch (action)
  {
    case Buttons_action::two_buttons_2s:
      m_data_presentation.display_calib_mode();
      m_device_state = Device_state::calibration_ec;
      break;
    case Buttons_action::right_button_2s:
      digitalWrite(Config::m_ec_supply_pin_probe, LOW);
      digitalWrite(Config::m_ph_supply_pin_probe, HIGH);
      m_device_state = Device_state::display_measure_ph;
      break;
    default:
      m_device_state = Device_state::display_measure_ec;
      break;
  }
}

bool save_sample(Point* samples, int sample)
{
  static int sample_counter = 0;
  samples[sample_counter].x = sample;
  // TODO: change ph/ec
  samples[sample_counter].y = analogRead(Config::m_ph_pin_probe);
  if (++sample_counter == 2)
  {
    sample_counter = 0;
    return true;
  }
  return false;
}

void calibration_ph(const Buttons_action action)
{
  static int sample = 4;

  static Point samples[2] = {};

  float temperature = m_ds_sensor.getTempC();

  switch (action)
  {
    case Buttons_action::two_buttons_2s:
      m_data_presentation.display_save_data();
      if (save_sample(samples, sample))
      {
        m_memory.save_ph_calibration(std::make_pair(samples[0], samples[1]));
        probe_characteristic.set_points(samples[0], samples[1]);
        m_device_state = Device_state::display_measure_ph;
      }
      break;
    case Buttons_action::short_left_button:
      sample--;
      break;
    case Buttons_action::short_right_button:
      sample++;
      break;
    default:
      m_data_presentation.display_calibration_ph(sample, temperature);
      break;
  }
}

void calibration_ec(Buttons_action action)
{
  static double sample = 4.0;

  static Point samples[2] = {};

  float temperature = m_ds_sensor.getTempC();

  switch (action)
  {
    case Buttons_action::two_buttons_2s:
      break;
    default:
      break;
  }
}

/**
 * @brief buttons action reaction
 * @return Buttons_action type of action was done
 */
Buttons_action check_buttons()
{
  long m_buttons_start_press;
  if (m_r_button_pressed || m_l_button_pressed)
  {
    m_buttons_start_press = millis();

    // przycisniecie dwoch przyciskow >2s
    do
    {
      long loop_time = millis();
      if (loop_time - m_buttons_start_press > Config::m_long_press_time)
      {
        m_l_button_pressed = false;
        m_r_button_pressed = false;
        return Buttons_action::two_buttons_2s;
      }
    } while (!digitalRead(Config::m_pin_r_button) && !digitalRead(Config::m_pin_l_button));

    // przycisniecie prawego przycisku >2s
    do
    {
      long loop_time = millis();
      if (loop_time - m_buttons_start_press > Config::m_long_press_time)
      {
        m_l_button_pressed = false;
        m_r_button_pressed = false;
        return Buttons_action::right_button_2s;
      }
    } while (!digitalRead(Config::m_pin_r_button) && digitalRead(Config::m_pin_l_button));
  }

  if (digitalRead(Config::m_pin_r_button) && digitalRead(Config::m_pin_l_button))
  {
    if (m_l_button_pressed)
    {
      m_l_button_pressed = false;
      return Buttons_action::short_left_button;
    }
    else if (m_r_button_pressed)
    {
      m_r_button_pressed = false;
      return Buttons_action::short_right_button;
    }
  }
  return Buttons_action::nothig;
}

/**
 * @brief setup on startup
 */
void setup()
{
  m_data_presentation.display_start();
  ds_thermometer_init();

  auto points = m_memory.load_ph_calibration();
  probe_characteristic.set_points(points);

  pinMode(Config::m_ph_supply_pin_probe, OUTPUT);
  digitalWrite(Config::m_ph_supply_pin_probe, HIGH);
  pinMode(Config::m_ec_supply_pin_probe, OUTPUT);
  digitalWrite(Config::m_ec_supply_pin_probe, LOW);
  pinMode(Config::m_pin_r_button, INPUT_PULLUP);
  pinMode(Config::m_pin_l_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_r_button), button_r_pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_l_button), button_l_pressed, FALLING);

  m_device_state = Device_state::display_measure_ph;
}

/**
 * @brief main loop with state machine
 */
void loop()
{
  auto action = check_buttons();
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