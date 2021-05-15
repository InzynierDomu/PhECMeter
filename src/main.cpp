#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Linear_function.h"

enum class Device_state
{
  startup,
  display_measure_ph,
  display_measure_ec,
  calibration_ph,
  calibration_ec
};

byte m_ds_address[8];
OneWire *m_one_wire = new OneWire(Config::m_pin_thermometer);
DS18B20 *m_ds_sensor = new DS18B20(Config::m_pin_thermometer);
Adafruit_SSD1306 display(Config::m_screen_width, Config::m_screen_height, &Wire);

Device_state m_device_state = Device_state::startup;

long m_buttons_start_press;
bool m_r_button_pressed = false;
bool m_l_button_pressed = false;
bool m_calibration = false;
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

void screen_init()
{
	display.begin(SSD1306_SWITCHCAPVCC, Config::m_screen_adress);
  	display.clearDisplay();
  	display.setTextSize(2);      
  	display.setTextColor(SSD1306_WHITE); 
  	display.display();
}

void button_r_pressed()
{
	m_buttons_start_press = millis();
	m_r_button_pressed = true;
}

void button_l_pressed()
{
	m_buttons_start_press = millis();
	m_l_button_pressed = true;
}

void display_start()
{
	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.println("pH meter");
	display.setTextSize(1);
	display.println("inzynier Domu");
  	display.display();
	display.setTextSize(2);
}

void display_calib_mode()
{
	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.println("CALIB");
	display.println("MODE");
  	display.display();
}

void display_save_data()
{
	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.println("POINT");
	display.println("SAVED");
  	display.display();
}

void display_measurements_ph()
{
	float temperature = m_ds_sensor->getTempC();
	int analog_mes = analogRead(Config::m_pin_probe);
	float ph = probe_characteristic.find_y(analog_mes);
//----------------------------------
	Serial.print("measure");
	Serial.print(temperature);
	Serial.print(";");
	Serial.print(analog_mes);
	Serial.print(";");
	Serial.println(ph);
//----------------------------------
	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.print(temperature); 
  	display.print((char)247);
	display.println("C");
	display.print(ph);
	display.print("pH");
  	display.display();
//----------------------------------

  if(m_r_button_pressed || m_l_button_pressed)
  {		
	do
	{
   	  long loop_time = millis();
	  if(loop_time - m_buttons_start_press > Config::m_long_press_time)
		{
		  m_device_state = Device_state::calibration_ph;
		}
	}
	while(!digitalRead(Config::m_pin_r_button) && !digitalRead(Config::m_pin_r_button));
		m_r_button_pressed = false;
		m_l_button_pressed = false;
  }
}

void display_calibration(int sample)
{
	long loop_time = millis();
	static long time;
	static bool toggle;

	float temperature = m_ds_sensor->getTempC();

	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.print(temperature); 
	display.print((char)247);
	display.println("C");

	if (loop_time - time > Config::blink_time_calibration) 
	{
		time = millis();
		toggle = !toggle;
	}
	
	if(toggle)
	{
		display.print(sample);
		display.print(".0 pH");	
	}
  	display.display();
}

void save_calibration(const Point samples[2])
{
	EEPROM.put<uint16_t>(0, samples[0].x);
	EEPROM.put<uint16_t>(4, samples[0].y);
	EEPROM.put<uint16_t>(8, samples[1].x);
	EEPROM.put<uint16_t>(12, samples[1].y);

	probe_characteristic.set_points(samples[0], samples[1]);  
}

void calibration_ph()
{
	bool save = false;
	static int sample = 4;
	static int calibrated_sample = 1;
	static Point samples[2]={};

	if(m_r_button_pressed || m_l_button_pressed)
	{
		delay(100);
		while (!digitalRead(Config::m_pin_r_button) && !digitalRead(Config::m_pin_r_button) && (m_r_button_pressed || m_l_button_pressed))
		{
			long loop_time = millis();
			if(loop_time - m_buttons_start_press > Config::m_long_press_time && !save)
			{
				if(calibrated_sample == 1)
				{					
					samples[0].x = sample;
					samples[0].y = analogRead(Config::m_pin_probe);				
					calibrated_sample++;
				}
				else
				{
					samples[1].x = sample;
					samples[1].y = analogRead(Config::m_pin_probe);
					save = true;					
				}
				display_save_data();
				
				m_r_button_pressed = false;	
				m_l_button_pressed = false;		
			}
		}
		
		if(m_r_button_pressed)
		{
			sample++;
		}

		else
		{
			sample--;	
		}

		m_r_button_pressed = false;	
		m_l_button_pressed = false;
	}

	if(save)
	{
		calibrated_sample = 1;
		save = false;
		m_calibration = false;
		save_calibration(samples);
	}	
	else
	{
		display_calibration(sample);
	}
}

void setup() 
{
  Serial.begin(9600);
  ds_thermometer_init();
  screen_init();
  display_start();

  uint16_t read_value_x;
  uint16_t read_value_y;
  EEPROM.get<uint16_t>(0,read_value_x);
  EEPROM.get<uint16_t>(4,read_value_y);
  Point first_sample(read_value_x, read_value_y);
  EEPROM.get<uint16_t>(8,read_value_x);
  EEPROM.get<uint16_t>(12,read_value_y);
  Point second_sample(read_value_x, read_value_y);

  probe_characteristic.set_points(first_sample, second_sample);

  pinMode(Config::m_supply_pin_probe, OUTPUT);
  digitalWrite(Config::m_supply_pin_probe, HIGH);
  pinMode(Config::m_pin_r_button, INPUT_PULLUP);
  pinMode(Config::m_pin_l_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_r_button), button_r_pressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(Config::m_pin_l_button), button_l_pressed, FALLING);

  m_device_state = Device_state::display_measure_ph; //startup finished
}

void loop() 
{
	switch (m_device_state)
	{
	case Device_state::display_measure_ph :
		display_measurements_ph();
		break;
	case Device_state::display_measure_ec :
		break;
	case Device_state::calibration_ph :
		calibration_ph();
		break;
	case Device_state::calibration_ec :
		break;
	default:
		break;
	}
}