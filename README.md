# PhECMeter

![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/InzynierDomu/PhECMeter/main.yml?logo=github&style=flat-square)
![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/InzynierDomu/PhECMeter?style=flat-square)
<a href="https://inzynierdomu.github.io/PhECMeter/">![GitHub docs deployments](https://img.shields.io/github/deployments/InzynierDomu/PhECMeter/github-pages?label=docs&logo=BookStack&logoColor=white&style=flat-square)</a>
<a href="https://discord.gg/KmW6mHdg">![Discord](https://img.shields.io/discord/815929748882587688?logo=discord&logoColor=green&style=flat-square)</a>
![GitHub](https://img.shields.io/github/license/InzynierDomu/PhECMeter?style=flat-square)
<a href="https://tipo.live/p/inzynierdomu">![support](https://img.shields.io/badge/support-tipo.live-yellow?style=flat-square)</a>

- [PhECMeter](#phecmeter)
  - [Description](#description)
    - [Future](#future)
  - [Scheme](#scheme)
    - [Part list](#part-list)
  - [IDE](#ide)

## Description
The video with the entire project can be watched on this [video](https://youtu.be/vjk0nq04lCo)

The device has 4 possible states:
* measure pH
* measure EC
* calibartion pH
* calibration EC

![photo](https://www.inzynierdomu.pl/wp-content/uploads/2019/12/IMG_5993-scaled.jpg)

The device start in pH measure mode. To chnage pH/EC measure mode - press up button for more than 1s.</br>
To enter calibration mode press both buttons more 1s.</br>
Measure pH -> calibration pH.</br>
Measure EC -> calibartion EC.</br>
Calibration mode needs 2 points to save.</br>
Set the value to which sample the probe is immersed. For that use up and dwn(down) buttons to decrease or increase the value. In EC calibration possible is to change the digit position by pressing 1s up button. To save points press 1s on both buttons. After saving two points, the device changes state to measure.</br>
</br>
When SD card is plugged, after short press down button measurements will be save in file on SD.

### Future
* Use accumulator.
* Add some communication maybe RS232 or RS485.

## Scheme
![schem](https://github.com/InzynierDomu/PhECMeter/blob/master/schems/electrical/Screen.png)
### Part list
* pH probe and board like [this](https://botland.com.pl/pl/seria-gravity/15094-gravity-czujnik-miernik-ph-analogowy-v2-dfrobot-sen0161-v2.html?utm_source=blog&utm_medium=link&utm_campaign=inzynierdomu)
* EC probe and board like [this](https://botland.com.pl/gravity-czujniki-pogodowe/15096-gravity-analogowy-czujnik-zasolenia-wody-i-gleby-dfrobot-dfr0300-h-5904422348359.html?utm_source=blog&utm_medium=link&utm_campaign=inzynierdomu)
* A1 Arduino Nano
* U1 ds18b20 temperature sensor
* J1 is socket for pH board.
* J2 is socket for I2C screen OLED SSD1306 128x32 or HD44780 via PCF8574. 
* R1 Resistor 4,7 kohm
* SW1, SW2 micro switch
* SW3 switch to turning on/of power
* J3 connect to battery box
* J5 SD card socket (optional)

## IDE
For specific screen is the prepared environment:</br>
OLED SSD1306 128x32 :nanoatmega328_oled</br>
HD44780 via PCF8574 :nanoatmega328_lcd</br>
</br>
The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc).
<br><br>
Formatting is done using clang-format. The description of the tool configuration is in the [video](https://youtu.be/xxuaOG0WjIE).
<br><br>
The code contains a comment prepared for doxygen, their use is described in the [video](https://youtu.be/1YKJtrCsPD4).
