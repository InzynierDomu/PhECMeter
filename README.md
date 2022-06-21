# PhMeter
* [Scheme](#Scheme)
* [IDE](#IDE)

The video with the entire project can be watched on this [video](https://youtu.be/vjk0nq04lCo)
## Scheme
![alt text](http://www.inzynierdomu.pl/wp-content/uploads/2021/01/ph_metr_schemat.png)
### Part list:
* pH metr need probe and board for probe like [this](https://botland.com.pl/pl/seria-gravity/15094-gravity-czujnik-miernik-ph-analogowy-v2-dfrobot-sen0161-v2.html?utm_source=blog&utm_medium=link&utm_campaign=inzynierdomu)
* A1 Arduino Nano
* U1 ds18b20 temperature sensor
* J1 is socket for pH board.
* J2 is socket for I2C oled screen SSD1306 128x32.
* R1 Resistor 4,7 kohm
* SW1, SW2 micro switch
* SW3 switch to turning on/of power
* J3 connect to battery box
## IDE
The project is prepared for the Platform IO environment. A video on how to install such an environment can be watched on this [video](https://youtu.be/Em9NuebT2Kc).
<br><br>
Formatting is done using clang-format. The description of the tool configuration is in the [video](https://youtu.be/xxuaOG0WjIE).
<br><br>
The code contains a comment prepared for doxygen, their use is described in the [video](https://youtu.be/1YKJtrCsPD4).
