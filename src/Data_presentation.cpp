#include "Data_presentation.h"

#include "Config.h"

#include <math.h>

Data_presentation::Data_presentation()
: m_display(Config::m_screen_width, Config::m_screen_height, &Wire)
{
  m_display.begin(SSD1306_SWITCHCAPVCC, Config::m_screen_adress);
  m_display.clearDisplay();
  m_display.setTextSize(2);
  m_display.setTextColor(SSD1306_WHITE);
  m_display.display();
}

void Data_presentation::display_start()
{
  Serial.begin(9600);

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.setTextSize(1);
  m_display.println("pH/EC meter");
  m_display.println("inzynier Domu");
  m_display.display();
  m_display.setTextSize(2);
  delay(500);
}

void Data_presentation::display_calib_mode()
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.println("CALIB");
  m_display.println("MODE");
  m_display.display();
  delay(500);
}

void Data_presentation::display_save_data()
{
  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.println("POINT");
  m_display.println("SAVED");
  m_display.display();
  delay(500);
}

void Data_presentation::presentation_measurements_ph(const float temperature, const float ph)
{
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(ph);

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");
  m_display.print(ph);
  m_display.print("pH");
  m_display.display();
}

void Data_presentation::presentation_measurements_ec(const float temperature, const float ec)
{
  Serial.print(temperature);
  Serial.print(",");
  Serial.println(ec);

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");
  m_display.print(ec);
  m_display.print("?");
  m_display.display();
}

void Data_presentation::display_calibration_ph(const uint8_t sample, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  if (toggle)
  {
    m_display.print(sample);
  }
  else
  {
    m_display.print(" ");
  }

  m_display.print(".0 pH");
  m_display.display();

  // 1.0 pH
  //  .0 pH
  // 1.0 pH
  // 0.0 pH
  //  .0 pH
}

void Data_presentation::display_calibration_ec(const double sample, const int position, const float temperature)
{
  long loop_time = millis();
  static long time;
  static bool toggle;
  // static sample_position = 1;

  // 1.00
  // .0
  // 1.0
  // 1.
  // 1.1
  // 1.

  // 1.

  m_display.clearDisplay();
  m_display.setCursor(0, 0);
  m_display.print(temperature);
  m_display.print((char)247);
  m_display.println("C");

  if (loop_time - time > Config::blink_time_calibration)
  {
    time = millis();
    toggle = !toggle;
  }

  double fractpart, intpart;
  fractpart = modf(sample, &intpart);
  if (toggle)
  {}
  else
  {}

  m_display.display();
}