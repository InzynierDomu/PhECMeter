/**
 * @file Automation.cpp
 * @author by Szymon Markiewicz (https://github.com/InzynierDomu/)
 * @brief regulation ph and ec
 * @date 2022-09
 */

#include "Automation.h"

Automation::Automation(const double max_ph, const double max_ec)
: m_max_ph(max_ph)
, m_max_ec(max_ec)
{}
void Automation::change_max_ph(const double max_ph) {}
void Automation::change_max_ec(const double max_ec) {}
bool Automation::check_ph_value(const double value) {}
bool Automation::check_ec_value(const double value) {}
void Automation::turn_on_fill_ph() {}
void Automation::turn_on_fill_ec() {}
void Automation::turn_off_fill_ph() {}
void Automation::turn_off_fill_ec() {}