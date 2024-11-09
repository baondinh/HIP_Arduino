// To Do: 
// Implement millis() instead of delay() function to track time
// millis() is non-blocking while delay() is blocking --> Blocking: Pauses program instead of continuing program and noting time

// CSB: pin 10 chip select pin
// MOSI: pin 11 (COPI)
// MISO: pin 12 (CIPO)
// SCK: pin 13
// the sensor communicates using SPI, so include the library:
#include <SPI.h>

bool active = false; // Feedback variable
unsigned long startTime; 
unsigned long runningTime;
// int timer = 0; // Timer to track rocket firing time

int chipSelectPin = 10; 
void setup(){
  Serial.begin(9600); // Serial communication 9600 bits per second
  // Start SPI library
  SPI.begin();
  
  pinMode(2, INPUT);	// D2 INPUT, digital signal from button
  pinMode(8, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(9, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  pinMode(chipSelectPin, OUTPUT); // D10 OUTPUT, should be set to 0 to select SD card for communication
  
  // These pins should be controlled by SPI library
  // pinMode(11, OUTPUT); // D11 OUTPUT, MOSI line to SD card 
  // pinMode(12, OUTPUT); // D12 OUTPUT, MISO line to SD card 
  // pinMode(13, OUTPUT); // D13 OUTPUT, use as digital clk
  // digitalWrite(10, 0); // Client select
}


// Change delay to timer instead
void loop() {
  // delay(500); // 0.5s delay between readings
  int buttonState = digitalRead(2); // D2 button signal read
  if (buttonState == 1 && !active) {	
    active = true; // To prevent redundant signals if someone spams button
    digitalWrite(9, 1); // D9 Digital signal to open solenoid
    digitalWrite(8, 1); // D8 Digital signal to light E-match
    startTime = millis(); // Begin tracking time (milliseconds since program started)
    delay(1000); // 1s pulse
    digitalWrite(8, 0); // D8 Digital signal to turn-off E-match
  } 
  inByte = Serial.read();  // D0/RX Read serial data from ADC → 2’s complement 24 bits

  digitalWrite(11, x); // D11 send unknown value to MOSI
  Serial.write(data); // D1/TX write serial data → Need to interpret 2’s complement 24 bits
  runningTime = millis(); // Keep track of running time
  if active {
    if (runningTime - startTime) >= 3000 { //3s
      digitalWrite(9, 0); // D9 Digital signal to close solenoid
      active = false; // Reset active status
      timer = 0; // Reset timer
    }
  }
}

// serial_data_interpretation → Interpreting 2’s complement 24 bits sent from ADC
int readRegister(byte thisRegister, int bytesToRead) {
  byte inByte = 0; 
  int result = 0; 

  byte dataToSend = READ;
  
  // LOW chip select to select SD card
  digitalWrite(chipSelectPin, LOW); 
  SPI.transfer(dataToSend); 

  result = SPI.transfer(0x00);
  bytesToRead--;

  while (bytesToRead > 0) {
    result = result << 8; 
    inByte = SPI.transfer(0x00); 
    result = result | inByte;
    bytesToRead--;
  }

  digitalWrite(chipSelectPin, HIGH); 
  return(result);   
}
