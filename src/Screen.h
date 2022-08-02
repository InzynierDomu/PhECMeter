#pragma once

#ifdef LCD_SCREEN
#include <Wire.h> 
#include "LiquidCrystal_I2C.h"
#else
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#endif