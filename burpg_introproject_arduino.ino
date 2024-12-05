// From HX711 sheet, OUT registers R4, R5, R7, R7 with R7 LSB

// millis() is non-blocking while delay() is blocking --> Blocking: Pauses program instead of continuing program and noting time

// CSB: pin 10 chip select pin
// MOSI: pin 11 (COPI)
// MISO: pin 12 (CIPO)
// SCK: pin 13
// the sensor communicates using SPI, so include the library:
#include <SPI.h>
// #include <HX711_ADC.h>

bool active = false; // Feedback variable

// millis timings
unsigned long startTime; 
unsigned long runningTime;
int period = 3000;

// Could also use analog pins
// const int LOADCELL_DOUT_PIN = 4;
// const int LOADCELL_SCK_PIN = 5;
// HX711_ADC LoadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); 

const int BUTTON_PIN = 2; 
const int EMATCH_PIN = 8; 
const int SOLENOID_PIN = 9; 
const int SELECT_PIN = 10; 

void setup(){
  Serial.begin(9600); // Serial communication 9600 bits per second
  // Start SPI library
  SPI.begin();

  pinMode(BUTTON_PIN, INPUT);	// D2 INPUT, digital signal from button
  pinMode(EMATCH_PIN, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(SOLENOID_PIN, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  pinMode(SELECT_PIN, OUTPUT); // D10 OUTPUT, should be set to 0 to select SD card for communication

  // LoadCell.begin();
}


// Change delay to timer instead
void loop() {
  // delay(500); // 0.5s delay between readings
  int buttonState = digitalRead(BUTTON_PIN); // D2 button signal read
  if (buttonState == 1 && !active) {	
    active = true; // To prevent redundant signals if someone spams button    
    digitalWrite(SOLENOID_PIN, 1); // D9 Digital signal to open solenoid
    delay(2000); 
    digitalWrite(EMATCH_PIN, 1); // D8 Digital signal to light E-match
    // readADC(); 
    startTime = millis(); 
  } else if (active) {
    while (millis() < startTime + period) { 
        // Non-blocking wait period to ensure 3 second firing before closing solenoid 
        readADC();
      }
      digitalWrite(SOLENOID_PIN, 0); // D9 Digital signal LOW to close solenoid
      active = false; // Reset active flag
  } else { //Neutral state when button has not been pressed and there is no active ignition sequence
    digitalWrite(SOLENOID_PIN, 0); // D9 Digital signal to open solenoid
    digitalWrite(EMATCH_PIN, 0); // D8 Digital signal to light E-match
  }
 
  //Placeholding register for memory register of HX711 output
  // int thrust = readRegister(place_reg, 3);
  // digitalWrite(11, x); // D11 send unknown value to MOSI
}

// Function to read HX711 output with HX711 library 
// void readADC() {
//     if (scale.is_ready()) {
//           long reading = scale.read();
//           Serial.print("HX711 reading: ");
//           Serial.println(reading);
//           if (reading >= limitValue){
//               digitalWrite(switchPin, HIGH);   // turn the PIN on (HIGH is the voltage level)
//           } else {
//               digitalWrite(switchPin, LOW);    // turn the PIN off by making the voltage LOW
//               delay(1000);
//           }
//       } else {
//           Serial.println("HX711 not found.");
//       }
// }

// // serial_data_interpretation → Interpreting 2’s complement 24 bits sent from ADC
// int readRegister(byte thisRegister, int bytesToRead) {
//   byte inByte = 0; 
//   // No 24-bit data type, would need logic for the final result to be an integer
//   int result = 0; 

//   byte dataToSend = READ;
  
//   // LOW chip select to select SD card
//   digitalWrite(chipSelectPin, LOW); 
//   SPI.transfer(dataToSend); 

//   // SPI transfer simultaneous send and receive
//   result = SPI.transfer(0x00);
//   bytesToRead--;

//   while (bytesToRead > 0) {
//     result = result << 8; 
//     inByte = SPI.transfer(0x00); 
//     result = result | inByte;
//     bytesToRead--;
//   }

//   digitalWrite(chipSelectPin, HIGH); 
//   return(result);   
// }

// // Not used but included 
// void writeRegister(byte thisRegister, byte thisValue) {
//   byte dataToSend = thisRegister | WRITE;

//   digitalWrite(chipSelectPin, LOW); 

//   SPI.transfer(dataToSend); //Send register location 
//   SPI.transfer(thisValue); //Send value to record into register

//   digitalWrite(chipSelectPin, HIGH); 
// }
