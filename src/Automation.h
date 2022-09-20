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
  Automation(const double max_ph, const double max_ec);
  void change_max_ph(const double max_ph);
  void change_max_ec(const double max_ec);
  bool check_ph_value(const double value);
  bool check_ec_value(const double value);

  private:
  double m_max_ph;
  double m_max_ec;  

  void turn_on_fill_ph();
  void turn_on_fill_ec();
  void turn_off_fill_ph();
  void turn_off_fill_ec();
};