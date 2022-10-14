/**
 * @file Automation.h
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief regulation ph and ec
 * @date 2022-09
 */

#pragma once

class Automation
{
  public:
  Automation(const double min_ph = 0, const double min_ec = 0);
  void set_min_ph(const double min_ph);
  void set_min_ec(const double min_ec);
  bool check_ph_value(const double value);
  bool check_ec_value(const double value);
  void disable();

  private:
  double m_min_ph; ///< minimal correct ph level
  double m_min_ec; ///< minimal correct ec level
  bool m_disable;

  void turn_on_fill_ph();
  void turn_on_fill_ec();
  void turn_off_fill_ph();
  void turn_off_fill_ec();
};