/**
 * @file Config.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief device configuration
 * @date 2022-06
 */
#pragma once

#include <Arduino.h>
#include <stdint.h>

namespace Config
{
const uint8_t pin_up_button = 3; ///< up button pin
const uint8_t pin_down_button = 2; ///< down button pin
const uint8_t pin_thermometer = 7; ///< ds18b20 thermometer pin
const uint8_t ph_pin_probe = 15; ///< ph probe pin
const uint8_t ec_pin_probe = 16; ///< ec probe pin
const uint8_t ph_supply_pin_probe = 9; ///< ph probe supply pin
const uint8_t ec_supply_pin_probe = 8; ///< ec probe supply pin
const uint8_t sd_card_cs_pin = 10; ///< cs pin in spi communication to sd card

const uint8_t screen_address = 0x3C; ///< ssd1306 oled screen i2c address
const uint8_t screen_width = 128; ///< screen width
const uint8_t screen_height = 32; ///< screen height

const uint8_t blink_time_calibration = 150; ///< toggling digits in calibration mode time
const uint16_t long_press_time = 1000; ///< time for long buttons press
const uint8_t max_ph_to_calib = 24; ///< max ph to set in calibration
const uint8_t max_ec_to_calib = 64; ///< max ec to set in calibration

const String file_name = "data.log"; ///< file name on SD card to save measurments

const uint8_t pin_left_button = 4; ///< left button pin
const uint8_t pin_right_button = 5; ///< right button pin
const uint8_t pin_center_button = 6; ///< center button pin
const uint8_t pin_ph_relay = 13; ///< ph control relay pin
const uint8_t pin_ec_relay = 14; ///< ec control relay pin
const uint8_t pin_enable_automation = 17; ///< enable/disable automation input pin

const uint8_t ports_with_interrupt = B00000100; ///< port D
const uint8_t pins_interrupt_D = B01111100; ///< buttons pin on port D

} // namespace Config