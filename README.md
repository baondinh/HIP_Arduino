PSEUDOCODE

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


