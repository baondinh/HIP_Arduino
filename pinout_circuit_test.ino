#include <SPI.h>

// After four tests of sending HIGH and LOW input signals to D2, the Arduino seems to freeze
// There could be a short circuit or some sort of memory leak/overflow causing the Arduino to freeze

// Load cell library (Commented out for testing)
// #include <HX711_ADC.h>

int period = 500;
int counter = 0; 

void setup() {
  Serial.begin(9600); // Serial communication 9600 bits per second

  // Start SPI library
  SPI.begin();
  
  pinMode(2, INPUT);  // D2 INPUT, digital signal from button
  pinMode(8, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(9, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  // pinMode(chipSelectPin, OUTPUT); // D10 OUTPUT, should be set to 0 to select SD card for communication
}

void loop() {
      int buttonState = digitalRead(2);

      if (buttonState == 1) { 
        // active = true; // To prevent redundant signals if someone spams button
        digitalWrite(9, 1); // D9 Digital signal to open solenoid
        delay(2000);
        digitalWrite(8, 1); // D8 Digital signal to light E-match
        // int startTime = millis(); // Begin tracking time (milliseconds since program started)
      } else {
        digitalWrite(9, 0); // D9 Digital signal to open solenoid
        digitalWrite(8, 0); // D8 Digital signal to light E-match
      }


      int startTime = millis(); // Begin tracking time (milliseconds since program started)
      while (millis() < startTime + period) { 
          //wait time
      }
      Serial.println("\nSample " + (String)counter);
      Serial.println("Pin2(Button): " + (String)digitalRead(2));
      Serial.println("Pin8(Ematch): " + (String)digitalRead(8));
      Serial.println("Pin9(solenoid) " + (String)digitalRead(9));
      counter += 1; 
}
