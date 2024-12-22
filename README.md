12/22/24 Notes: 
- Hotfire scheduled for next semseter
- Need to include load cell reading and SD card in future (update Arduino code and solder after testing)

Arduino Specific Notes: 
- Pin 2 --> Button
- Pin 4 --> Solenoid
- Pin 8 --> E-match

Arduino Nano 3.0 Microcontroller for use in BURPG intro project
- Using SPI library to connect to SD card and HX711 Load Cell Reader (ADC)
  - CSB: pin 10 chip select pin
  - MOSI: pin 11 (COPI)
  - MISO: pin 12 (CIPO)
  - SCK: pin 13
- SPI.h and SPI.cpp can be found in ArduinoCore-avr/libraries repo (added to project directory for faster viewing)

- https://forum.arduino.cc/t/what-is-the-simpelest-way-to-read-hx711-data/970254/2 for HX711 reading
