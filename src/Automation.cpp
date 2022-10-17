/**
 * @file Automation.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief regulation ph and ec
 * @date 2022-09
 */

#include "Automation.h"

#include "Arduino.h"
#include "Config.h"

/**
 * @brief Construct a new Automation:: Automation object
 * @param min_ph minimal ph value to fill
 * @param min_ec minimal ec value to fill
 */
Automation::Automation(const double min_ph, const double min_ec)
: m_min_ph(min_ph)
, m_min_ec(min_ec)
, m_disable(false)
{}

/**
 * @brief set new value for minimal ph
 * @param min_ph minimal ph value
 */
void Automation::set_min_ph(const double min_ph)
{
  m_min_ph = min_ph;
}

/**
 * @brief set new value for minimal ec
 * @param min_ec minimal ec value
 */
void Automation::set_min_ec(const double min_ec)
{
  m_min_ec = min_ec;
}

/**
 * @brief check is ph level is correct
 * @param value ph level
 * @return is ph level is to low
 */
bool Automation::check_ph_value(const double value)
{
  if (m_disable)
  {
    return false;
  }

  if (value < m_min_ph)
  {
    return true;
  }
  return false;
}

/**
 * @brief check is ec level is correct
 * @param value ec level
 * @return is ec level is to low
 */
bool Automation::check_ec_value(const double value)
{
  if (m_disable)
  {
    return false;
  }

  if (value < m_min_ec)
  {
    return true;
  }
  return false;
}

void Automation::disable()
{
  m_disable = true;
}

void Automation::enable()
{
  m_disable = false;
}

void Automation::turn_on_fill_ph()
{
  digitalWrite(Config::pin_ph_relay, HIGH);
}

void Automation::turn_on_fill_ec()
{
  digitalWrite(Config::pin_ec_relay, HIGH);
}

void Automation::turn_off_fill_ph()
{
  digitalWrite(Config::pin_ph_relay, LOW);
}

void Automation::turn_off_fill_ec()
{
  digitalWrite(Config::pin_ec_relay, LOW);
}