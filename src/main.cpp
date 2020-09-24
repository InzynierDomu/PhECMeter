#include <Arduino.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DS18B20.h>
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

struct Linear_function
{
  //y = ax + b
  double a;
  double b; 
};

struct Point
{
  Point(uint16_t _y = 0, uint16_t _x = 0):y(_y), x(_x){};
  uint16_t y;
  uint16_t x;
};

const byte m_pin_r_button = 3;
const byte m_pin_l_button = 2;
const byte m_pin_thermometer = 4;
const byte m_pin_probe = A1;

const byte m_screen_adress = 0x3C;    
const int m_screen_width = 128;
const int m_screen_height = 32; 

byte m_ds_address[8];
OneWire *m_one_wire = new OneWire(m_pin_thermometer);
DS18B20 *m_ds_sensor = new DS18B20(m_pin_thermometer);

Adafruit_SSD1306 display(m_screen_width, m_screen_height, &Wire);

const long m_long_press_time = 1000;
long m_buttons_start_press;
bool m_r_button_pressed = false;
bool m_l_button_pressed = false;
bool m_calibration = false;
Linear_function probe_characteristic;

Linear_function calculate(Point first, Point second)
{
  Linear_function f;
  f.a = (second.y - first.y)/(double)(second.x - first.x);
  f.b = first.y - (f.a * first.x);
  return f;
}

double find_y(int x, Linear_function f)
{
  return(f.a * x + f.b);
}

void ds_thermometer_init()
{
	Serial.print("Serch thermometer");
	m_one_wire->reset_search();
	while (m_one_wire->search(m_ds_address))
	{
		if (m_ds_address[0] != 0x28)
			continue;

		if (OneWire::crc8(m_ds_address, 7) != m_ds_address[7])
		{
			Serial.println(F("1-Wire bus connection error!"));
			break;
		}

		for (byte i = 0; i < 8; i++)
		{
			Serial.print(F("0x"));
			Serial.print(m_ds_address[i], HEX);

			if (i < 7)
				Serial.print(F(", "));
		}
		Serial.println();
	}
}

void screen_init()
{
	if(!display.begin(SSD1306_SWITCHCAPVCC, m_screen_adress)) { 
    	Serial.println(F("SSD1306 allocation failed"));
  	}
  	else
  	{
    	Serial.println(F("SSD1306 allocation ok"));
 	} 
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

void display_measurements()
{
	float temperature = m_ds_sensor->getTempC();
	int analog_mes = analogRead(m_pin_probe);
	float ph = find_y(analog_mes, probe_characteristic);

	Serial.print("measure");
	Serial.print(temperature);
	Serial.print(";");
	Serial.print(analog_mes);
	Serial.print(";");
	Serial.println(ph);

	display.clearDisplay();
  	display.setCursor(0, 0);   
  	display.print(temperature); 
  	display.print((char)247);
	display.println("C");
	display.print(ph);
	display.print("pH");
  	display.display();
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

	if (loop_time - time > 150) 
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

	Serial.print("EEPROM_save_0_1");
	uint16_t read_value;
	EEPROM.get<uint16_t>(0,read_value);
	Serial.print(read_value);
	Serial.print(",");
	EEPROM.get<uint16_t>(4,read_value);
	Serial.println(read_value);
	Serial.print("EEPROM_save_2_3");
	EEPROM.get<uint16_t>(8,read_value);
	Serial.print(read_value);
	Serial.print(",");
	EEPROM.get<uint16_t>(12,read_value);
	Serial.println(read_value);

	probe_characteristic = calculate(samples[0], samples[1]);  
}

void calibration()
{
	bool save = false;
	static int sample = 4;
	static int calibrated_sample = 1;
	static Point samples[2]={};

	if(m_r_button_pressed || m_l_button_pressed)
	{
		while (!digitalRead(m_pin_r_button) && !digitalRead(m_pin_r_button) && (m_r_button_pressed || m_l_button_pressed))
		{
			long loop_time = millis();
			if(loop_time - m_buttons_start_press > m_long_press_time && !save)
			{
				if(calibrated_sample == 1)
				{
					
					samples[0].x = sample;
					samples[0].y = analogRead(m_pin_probe);	
					Serial.print("sample_0");
					Serial.print(samples[0].x);
					Serial.print(",");
					Serial.println(samples[0].y);			
					calibrated_sample++;
				}
				else
				{
					samples[1].x = sample;
					samples[1].y = analogRead(m_pin_probe);
					Serial.print("sample_1");
					Serial.print(samples[1].x);
					Serial.print(",");
					Serial.println(samples[1].y);
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
	Serial.print("EEPROM_load_0_1");
	EEPROM.get<uint16_t>(0,read_value_x);
	Serial.print(read_value_x);
	Serial.print(",");
	EEPROM.get<uint16_t>(4,read_value_y);
	Serial.println(read_value_y);
	Point first_sample(read_value_x, read_value_y);
	Serial.print("EEPROM_load_2_3");
	EEPROM.get<uint16_t>(8,read_value_x);
	Serial.print(read_value_x);
	Serial.print(",");
	EEPROM.get<uint16_t>(12,read_value_y);
	Serial.println(read_value_y);
	Point second_sample(read_value_x, read_value_y);

  	probe_characteristic = calculate(first_sample, second_sample);  

	pinMode(m_pin_r_button, INPUT_PULLUP);
	pinMode(m_pin_l_button, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(m_pin_r_button), button_r_pressed, FALLING);
	attachInterrupt(digitalPinToInterrupt(m_pin_l_button), button_l_pressed, FALLING);
}

void loop() 
{
	if (m_calibration)
	{
		calibration();
	}
	else if(m_r_button_pressed || m_l_button_pressed)
	{		
		do
		{
			long loop_time = millis();
			if(loop_time - m_buttons_start_press > m_long_press_time)
			{
				m_calibration = true;
				display_calib_mode();
			}
		}
		while(!digitalRead(m_pin_r_button) && !digitalRead(m_pin_r_button) && !m_calibration);
		m_r_button_pressed = false;
		m_l_button_pressed = false;
	}
	else
	{
		display_measurements();
	}
}