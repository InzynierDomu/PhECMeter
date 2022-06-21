/**
 * @file Config.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief device configuration
 * @date 2022-06
 */
#pragma once

namespace Config
{
const uint8_t m_pin_r_button = 3; ///< right button pin number
const uint8_t m_pin_l_button = 2; ///< left button pin number
const uint8_t m_pin_thermometer = 4; ///< ds18b20 thermometer pin number
const uint8_t m_ph_pin_probe = 15; ///< ph probe pin
const uint8_t m_ec_pin_probe = 16; ///< ec probe pin
const uint8_t m_ph_supply_pin_probe = 5; ///< ph probe supply pin
const uint8_t m_ec_supply_pin_probe = 6; ///< ec probe supply pin

const uint8_t m_screen_address = 0x3C; ///< ssd1306 oled screen i2c address
const uint8_t m_screen_width = 128; ///< screen width
const uint8_t m_screen_height = 32; ///< screen height

const uint8_t blink_time_calibration = 150; ///< toggling digits in calibration mode time
const uint16_t m_long_press_time = 2000; ///< time for long buttons press

} // namespace Config