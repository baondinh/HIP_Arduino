// Variables 
button_state = 0; // Use input 

void setup(){
  // Setup code run only once
  // Open serial port and set data rate to 9600 bits per second
  Serial.begin(9600); 
  Serial.println("Arduino Setup Test");
  delay(2000); //delay for 2000 milliseconds or 2 seconds
}

void loop() {
  // Main code run repeatedly
  /* 
  1. Sample load cell every 0.5s (ignition should be ~3s, so 0.5s allows for multiple data points before, during, and after ignition)
  2. Check if input button state high (button is pressed --> state == 1) 
  3. If button_state == 1, then: 
      Open solenoid
      Delay xs
      Trigger ematch spark (one time use but for good practice, turn off signal to spark) 
      Wait at least 3s to sample ignition 
      Close solenoid 

  Notes: 
  How to handle multiple button presses within a short time-span (how to handle someone mashing the button and prevent conflicting signals) 
  */ 
  delay(500) //0.5s delay for sampling
  // if 
} 
