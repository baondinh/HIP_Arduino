PSEUDOCODE

bool processing = false; // Feedback variable
int timer = 0; // Timer to track rocket 

void setup(){
  Serial.begin(9600); // Serial communication 9600 bits per second
  pinMode(5, INPUT);	// D2 INPUT, digital signal from button
  pinMode(10, INPUT);  // D7 INPUT, digital signal from ADC
  pinMode(13, INPUT); // D10 INPUT, should be set to 0
  pinMode(11, OUTPUT); // D8 OUTPUT, use as signal to E-match
  pinMode(12, OUTPUT); // D9 OUTPUT, use as signal to solenoid
  pinMode(14, OUTPUT); // D11 OUTPUT, MOSI line sending data from Arduino to SD card  
  pinMode(16, OUTPUT); // D13 OUTPUT, use as digital clk
  digitalWrite(13, 0); 
}

void loop() {
  delay(500) // 0.5s delay between readings
  int buttonState = digitalRead(5); // D2 button signal read
  if (buttonState == 1 && !processing) {	
    processing = true; // To prevent redundant signals if someone spams button
    digitalWrite(12, 1); // D9 Digital signal to open solenoid
    digitalWrite(11, 1); // D8 Digital signal to light E-match
  } 
  data = digitalRead(10); // D7 Read data from ADC 
  digitalWrite(14, data); // D11 send data to MOSI 
  if digitalRead(16) - 
}

