// Pin to which the fan control (via transistor) is connected
const int fanPin = 9; // Use a PWM-capable pin

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Fan "breath in" - increase speed
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(fanPin, speed);
    delay(10); // Adjust to control breath-in duration
  }

  // Optional hold at full speed
  delay(200);

  // Fan "breath out" - decrease speed
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(fanPin, speed);
    delay(10); // Adjust to control breath-out duration
  }

  // Optional pause at zero speed
  delay(200);
}
