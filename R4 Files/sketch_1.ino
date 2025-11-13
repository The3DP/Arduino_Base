const int fanPin = 9;          // Pin connected to the fan
const unsigned long interval = 5000;  // 5 seconds interval
const unsigned long burstDuration = 500; // burst duration in milliseconds

unsigned long previousMillis = 0;
bool fanOn = false;
unsigned long fanOnMillis = 0;

void setup() {
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);   // Make sure fan is off initially
}

void loop() {
  unsigned long currentMillis = millis();

  if (!fanOn && (currentMillis - previousMillis >= interval)) {
    // Time to start the burst
    digitalWrite(fanPin, HIGH);
    fanOn = true;
    fanOnMillis = currentMillis;
    previousMillis = currentMillis;  // reset the interval timer here
  }

  if (fanOn && (currentMillis - fanOnMillis >= burstDuration)) {
    // Burst duration over, turn fan off
    digitalWrite(fanPin, LOW);
    fanOn = false;
  }
}
