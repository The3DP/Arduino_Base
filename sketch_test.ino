// Blink the built-in LED on an Arduino Nano
// The LED is connected to digital pin 13.

void setup() {
  pinMode(13, OUTPUT); // Set pin 13 as an output
}

void loop() {
  digitalWrite(13, HIGH); // Turn the LED on
  delay(500);             // Wait 0.5 seconds
  digitalWrite(13, LOW);  // Turn the LED off
  delay(500);             // Wait 0.5 seconds
}
