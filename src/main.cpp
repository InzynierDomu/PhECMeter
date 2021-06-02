#include <Arduino.h>
#include <ArduinoSTL.h>
#include <EEPROM.h>

#include "Config.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "Linear_function.h"
#include "Data_presentation.h"
#include "Calibration_data_memory.h"

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
OneWire *m_one_wire = new OneWire(Config::m_pin_thermometer);
DS18B20 *m_ds_sensor = new DS18B20(Config::m_pin_thermometer);
Data_presentation *m_data_presentation;

Device_state m_device_state = Device_state::startup;

bool m_r_button_pressed = false;
bool m_l_button_pressed = false;
Linear_function probe_characteristic;

void ds_thermometer_init()
{
	m_one_wire->reset_search();
	while (m_one_wire->search(m_ds_address))
	{
		if (m_ds_address[0] != 0x28)
			continue;

		if (OneWire::crc8(m_ds_address, 7) != m_ds_address[7])
		{
			break;
		}
	}
}

void button_r_pressed()
{
	m_r_button_pressed = true;
}

void button_l_pressed()
{
	m_l_button_pressed = true;
}

void measurements_ph(Buttons_action action)
{
	float temperature = m_ds_sensor->getTempC();
	int analog_mes = analogRead(Config::m_pin_probe);
	float ph = probe_characteristic.find_y(analog_mes);

	m_data_presentation->presentation_measurements_ph(temperature, ph);

	switch (action)
	{
	case Buttons_action::two_buttons_2s:
    m_data_presentation->display_calib_mode(); 
		m_device_state = Device_state::calibration_ph;
		break;
	case Buttons_action::right_button_2s:
		m_device_state = Device_state::display_measure_ec;
	default:
		m_device_state = Device_state::display_measure_ph;
		break;
	}
}

void measurements_ec(Buttons_action action)
{
	float temperature = m_ds_sensor->getTempC();
	float ec;

	m_data_presentation->presentation_measurements_ec(temperature, ec);
	
	switch (action)
	{
	case Buttons_action::two_buttons_2s:
    m_data_presentation->display_calib_mode(); 
		m_device_state = Device_state::calibration_ec;
		break;
	case Buttons_action::right_button_2s:
		m_device_state = Device_state::display_measure_ph;
	default:
		m_device_state = Device_state::display_measure_ec;
		break;
	}
}

void save_ph_calibration(const Point samples[2])
{
	EEPROM.put<uint16_t>(0, samples[0].x);
	EEPROM.put<uint16_t>(4, samples[0].y);
	EEPROM.put<uint16_t>(8, samples[1].x);
	EEPROM.put<uint16_t>(12, samples[1].y);

	probe_characteristic.set_points(samples[0], samples[1]);  
}

bool save_sample(Point*  samples, int sample)
{
	static int sample_counter = 0;
	samples[sample_counter].x = sample;
	samples[sample_counter].y = analogRead(Config::m_pin_probe);				
	if(++sample_counter == 2)
	{
		sample_counter = 0;
		return true;
	}
	return false;
}

void calibration_ph(Buttons_action action)
{
	static int sample = 4;
	
	static Point samples[2]={};

  float temperature = m_ds_sensor->getTempC();

	switch (action)
	{
	case Buttons_action::two_buttons_2s:
	  m_data_presentation->display_save_data();
	  if (save_sample(samples, sample))
	  {
			save_ph_calibration(samples);					
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
		m_data_presentation->display_calibration_ph(sample, temperature);
		break;
	}
}

void calibration_ec(Buttons_action action)
{
	
}

void setup() 
{
  m_data_presentation = new Data_presentation();
  ds_thermometer_init();
  m_data_presentation->display_start();

//--------------------------------------------------------
  uint16_t read_value_x;
  uint16_t read_value_y;
  EEPROM.get<uint16_t>(0,read_value_x);
  EEPROM.get<uint16_t>(4,read_value_y);
  Point first_sample(read_value_x, read_value_y);
  EEPROM.get<uint16_t>(8,read_value_x);
  EEPROM.get<uint16_t>(12,read_value_y);
  Point second_sample(read_value_x, read_value_y);

  probe_characteristic.set_points(first_sample, second_sample);
//--------------------------------------------------------

  pinMode(Config::m_supply_pin_probe, OUTPUT);
  digitalWrite(Config::m_supply_pin_probe, HIGH);
  pinMode(Config::m_pin_r_button, INPUT_PULLUP);
  pinMode(Config::m_pin_l_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_r_button), button_r_pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_l_button), button_l_pressed, FALLING);

  m_device_state = Device_state::display_measure_ph; //startup finished
}

Buttons_action check_buttons()
{
	long m_buttons_start_press;
  	if(m_r_button_pressed || m_l_button_pressed)
  	{			  
		m_buttons_start_press = millis();  

		//przycisniecie dwoch przyciskow >2s
		do
		{
		long loop_time = millis();
		if(loop_time - m_buttons_start_press > Config::m_long_press_time)
			{		  
			m_l_button_pressed = false;
			m_r_button_pressed = false;
			return Buttons_action::two_buttons_2s;
			}
		}while(!digitalRead(Config::m_pin_r_button) && !digitalRead(Config::m_pin_l_button));

		//przycisniecie prawego przycisku >2s
		do
		{
		long loop_time = millis();
		if(loop_time - m_buttons_start_press > Config::m_long_press_time)
			{
			m_device_state = Device_state::display_measure_ec;
			m_l_button_pressed = false;
			m_r_button_pressed = false;
			return Buttons_action::right_button_2s;
			}
		}while (!digitalRead(Config::m_pin_r_button) && digitalRead(Config::m_pin_l_button));
  	}

  	if(digitalRead(Config::m_pin_r_button) && digitalRead(Config::m_pin_l_button))
  	{
		if(m_l_button_pressed)
		{
			m_l_button_pressed = false;
			return Buttons_action::short_left_button;
		}
		else if(m_r_button_pressed)
		{
			m_r_button_pressed = false;
			return Buttons_action::short_right_button;
		}
    	
  	}
	return Buttons_action::nothig;
}

void loop() 
{
	Buttons_action action = check_buttons();
	switch (m_device_state)
	{
	case Device_state::display_measure_ph :
		measurements_ph(action);
		break;
	case Device_state::display_measure_ec :
		measurements_ec(action);
		break;
	case Device_state::calibration_ph :
		calibration_ph(action);
		break;
	case Device_state::calibration_ec :
		calibration_ec(action);
		break;
	default:
		break;
	}	
}