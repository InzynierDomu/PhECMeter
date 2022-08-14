/**
 * @file Config.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief device configuration
 * @date 2022-06
 */
#pragma once

#include <stdint.h>
#include <Arduino.h>

namespace Config
{
const uint8_t pin_up_button = 3; ///< up button pin number
const uint8_t pin_dwn_button = 2; ///< down button pin number
const uint8_t pin_thermometer = 4; ///< ds18b20 thermometer pin number
const uint8_t ph_pin_probe = 15; ///< ph probe pin
const uint8_t ec_pin_probe = 16; ///< ec probe pin
const uint8_t ph_supply_pin_probe = 5; ///< ph probe supply pin
const uint8_t ec_supply_pin_probe = 6; ///< ec probe supply pin
const uint8_t sd_card_cs_pin = 7; ///< cs pin in spi communication to sd card

const uint8_t screen_address = 0x3C; ///< ssd1306 oled screen i2c address
const uint8_t screen_width = 128; ///< screen width
const uint8_t screen_height = 32; ///< screen height

const uint8_t blink_time_calibration = 150; ///< toggling digits in calibration mode time
const uint16_t long_press_time = 2000; ///< time for long buttons press
const uint8_t max_ph_to_calib = 24; ///< max ph to set in calibration
const uint8_t max_ec_to_calib = 64; ///< max ec to set in calibration

const String file_name = "Measurments.log"; ///< file name on SD card to save measurments

} // namespace Config