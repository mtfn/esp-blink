# ESP Blink

Lets you turn an LED on or off with your phone. Utilizes an ESP-01 WiFi module in serial communication with an Arduino Nano.
The `WifiAccessPoint` and `SerialBlink` sketches are loaded on the [ESP](https://github.com/esp8266/arduino) and Arduino, respectively.

The devices are connected via crossed RX and TX pins and share a common GND (something I didn't realize at first) despite having separate power sources.
LED plugged into Arduino D10 and GND.

Made at the prompting of my engineering teacher as part of a class research project.