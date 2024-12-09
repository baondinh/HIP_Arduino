// From HX711 sheet, OUT registers R4, R5, R7, R7 with R7 LSB

// millis() is non-blocking while delay() is blocking --> Blocking: Pauses program instead of continuing program and noting time

// CSB: pin 10 chip select pin
// MOSI: pin 11 (COPI)
// MISO: pin 12 (CIPO)
// SCK: pin 13
// the sensor communicates using SPI, so include the library:
#include <SPI.h>
// #include <HX711.h>

bool active = false; // Feedback variable

// millis timings
unsigned long startTime; 
unsigned long runningTime;

// Could also use analog pins
// const int LOADCELL_DOUT_PIN = 4;
// const int LOADCELL_SCK_PIN = 5;
// const int ADC_OUT_PIN = 6; 
// HX711 scale; 
// const int limitValue = 100000; //trigger value (currently arbitrary number)

const int BUTTON_PIN = 2; 
const int EMATCH_PIN = 8; 
const int SOLENOID_PIN = 4; 
// const int SELECT_PIN = 10; 

void setup(){
  Serial.begin(9600); // Serial communication 9600 bits per second
  // Start SPI library
  SPI.begin();

  pinMode(BUTTON_PIN, INPUT);	// D2 INPUT, digital signal from button
  pinMode(EMATCH_PIN, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(SOLENOID_PIN, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  // pinMode(SELECT_PIN, OUTPUT); // D10 OUTPUT, should be set to 0 to select SD card for communication

  // scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN); // D2 button signal read
  if (buttonState == 1 && !active) {	
    active = true; // To prevent redundant signals if someone spams button    
    digitalWrite(SOLENOID_PIN, 1); // D9 Digital signal to open solenoid
    startTime = millis();
    while (millis() < startTime + 300) { } // 300ms delay between solenoid opening and ematch lighting
    digitalWrite(EMATCH_PIN, 1); // D8 Digital signal to light E-match

    // Turning off ematch signal for testing
    startTime = millis();
    while (millis() < startTime + 300) { } // 300ms delay after ematch lighting lighting
    digitalWrite(EMATCH_PIN, 0); // D8 Digital signal to light E-match
  } else if (active) {
    startTime = millis(); 
    while (millis() < startTime + 3000) { } // 3s delay for firing period
      digitalWrite(SOLENOID_PIN, 0); // D9 Digital signal LOW to close solenoid
      active = false; // Reset active flag
  } else { //Neutral state when button has not been pressed and there is no active ignition sequence
    digitalWrite(SOLENOID_PIN, 0); // D9 Digital signal to open solenoid
    digitalWrite(EMATCH_PIN, 0); // D8 Digital signal to light E-match
  }

  // Reading from ADC
  // if (scale.is_ready()) {
  //   long reading = scale.read(); 
  //   Serial.println("HX711 ADC reading: " + (String)reading); 
  //   if (reading >= limitValue) {
  //     digitalWrite(ADC_OUT_PIN, 1); // digital out pin HIGH signal
  //   } else {
  //     digitalWrite(ADC_OUT_PIN, 0); // digital out pin LOW signal
  //   }
  // }
}
