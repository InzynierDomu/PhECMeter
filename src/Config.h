#pragma once

#include <Arduino.h>

namespace Config
{
const uint8_t m_pin_r_button = 3;
const uint8_t m_pin_l_button = 2;
const uint8_t m_pin_thermometer = 4;
const uint8_t m_ph_pin_probe = A1;
const uint8_t m_ec_pin_probe = A2;
const uint8_t m_ph_supply_pin_probe = 5;
const uint8_t m_ec_supply_pin_probe = 6;

const uint8_t m_screen_adress = 0x3C;
const uint8_t m_screen_width = 128;
const uint8_t m_screen_height = 32;

const uint8_t blink_time_calibration = 150;
const uint16_t m_long_press_time = 2000;

} // namespace Config