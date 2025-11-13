#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

unsigned long startTime = 0;
bool running = false;

void setup() {
  matrix.begin();
  matrix.clear();
}

void loop() {
  // Start the stopwatch when a button is pressed (simulate with delay here)
  if (!running) {
    delay(1000); // Wait before starting
    startTime = millis();
    running = true;
  }

  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - startTime;

  // Convert to seconds.milliseconds
  unsigned int seconds = elapsed / 1000;
  unsigned int millisPart = (elapsed % 1000) / 100; // Tenths of a second

  // Create a string like "12.3s"
  String timeStr = String(seconds) + "." + String(millisPart) + "s";

  // Scroll the time across the matrix
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);
  matrix.textFont(Font_5x7);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(timeStr);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
  
  delay(100);
}
