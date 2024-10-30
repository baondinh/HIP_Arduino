// // Variables 
// button_state = 0; // Use input 

// void setup(){
//   // Setup code run only once
//   // Open serial port and set data rate to 9600 bits per second
//   Serial.begin(9600); 
//   Serial.println("Arduino Setup Test");
//   delay(2000); //delay for 2000 milliseconds or 2 seconds
// }

// void loop() {
//   // Main code run repeatedly
//   /* 
//   1. Sample load cell every 0.5s (ignition should be ~3s, so 0.5s allows for multiple data points before, during, and after ignition)
//   2. Check if input button state high (button is pressed --> state == 1) 
//   3. If button_state == 1, then: 
//       Open solenoid
//       Delay xs
//       Trigger ematch spark (one time use but for good practice, turn off signal to spark) 
//       Wait at least 3s to sample ignition 
//       Close solenoid 

//   Notes: 
//   How to handle multiple button presses within a short time-span (how to handle someone mashing the button and prevent conflicting signals) 
//   */ 
//   delay(500) //0.5s delay for sampling
//   // if 
// } 

bool active = false; // Feedback variable
int timer = 0; // Timer to track rocket firing time

void setup(){
  Serial.begin(9600); // Serial communication 9600 bits per second
  pinMode(5, INPUT);	// D2 INPUT, digital signal from button
  pinMode(11, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(12, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  pinMode(13, OUTPUT); // D10 OUTPUT, should be set to 0 to select SD card for communication
  pinMode(14, OUTPUT); // D11 OUTPUT, MOSI line to SD card 
  pinMode(15, OUTPUT); // D12 OUTPUT, MISO line to SD card 
  pinMode(16, OUTPUT); // D13 OUTPUT, use as digital clk
  digitalWrite(13, 0); // Client select
}

void loop() {
  delay(500); // 0.5s delay between readings
  int buttonState = digitalRead(5); // D2 button signal read
  if (buttonState == 1 && !active) {	
    active = true; // To prevent redundant signals if someone spams button
    digitalWrite(12, 1); // D9 Digital signal to open solenoid
    digitalWrite(11, 1); // D8 Digital signal to light E-match
    delay(1000); // 1s pulse
    digitalWrite(11, 0); // D8 Digital signal to turn-off E-match
  } 
  inByte = Serial.read();  // D0/RX Read serial data from ADC → 2’s complement 24 bits

  digitalWrite(14, x); // D11 send unknown value to MOSI
  Serial.write(data); // D1/TX write serial data → Need to interpret 2’s complement 24 bits
  if active {
    timer += 0.5;
    if timer == 3 {
      digitalWrite(12, 0); // D9 Digital signal to close solenoid
      active = false; // Reset active status
      timer = 0; // Reset timer
    }
  }
}

// Other functions to implement
// clk_signal → Serial Peripheral Interface (SPI)?
// serial_data_interpretation → Interpreting 2’s complement 24 bits sent from ADC

