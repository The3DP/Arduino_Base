//////////////////////////////
// The3DP                   //
// matrix_effect_random.ino //
// November 6, 2025         //
//////////////////////////////

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint8_t frame[8][12];
unsigned long lastAddTime = 0;
int lightsAdded = 0;
const int maxLights = 20;
int addInterval = 1000;        // Start with 1 second
const int speedIncrease = 150; // Decrease interval by 150ms each cycle
const int minInterval = 50;    // Minimum speed limit
int cycleCount = 0;            // Track cycles for visual feedback

void setup() {
  matrix.begin();
  randomSeed(analogRead(0));   // Better random seed
  clearFrame();
}

void clearFrame() {
  memset(frame, 0, sizeof(frame)); // Faster clear using memset
}

void addRandomLight() {
  // Create list of empty positions for better distribution
  int emptyPositions[96][2]; // Max 8*12 = 96 positions
  int emptyCount = 0;
  
  // Find all empty positions
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 12; col++) {
      if (frame[row][col] == 0) {
        emptyPositions[emptyCount][0] = row;
        emptyPositions[emptyCount][1] = col;
        emptyCount++;
      }
    }
  }
  
  // If there are empty positions, pick one randomly
  if (emptyCount > 0) {
    int choice = random(emptyCount);
    frame[emptyPositions[choice][0]][emptyPositions[choice][1]] = 1;
  }
}

void eraseRowByRow() {
  // Variable erase speed - faster as cycles increase
  int eraseDelay = max(20, 120 - (cycleCount * 10));
  
  // Erase from top to bottom with visual effect
  for (int row = 0; row < 8; row++) {
    // Flash the row before erasing
    for (int col = 0; col < 12; col++) {
      if (frame[row][col] == 1) {
        frame[row][col] = 0;
        matrix.renderBitmap(frame, 8, 12);
        delay(eraseDelay / 4);
        frame[row][col] = 1;
        matrix.renderBitmap(frame, 8, 12);
        delay(eraseDelay / 4);
        frame[row][col] = 0;
      }
    }
    matrix.renderBitmap(frame, 8, 12);
    delay(eraseDelay);
  }
}

void showCycleIndicator() {
  // Brief flash to show cycle number (1-5 flashes)
  clearFrame();
  matrix.renderBitmap(frame, 8, 12);
  delay(200);
  
  int flashes = min(cycleCount + 1, 5); // Max 5 flashes
  for (int i = 0; i < flashes; i++) {
    // Light up center area
    for (int row = 3; row < 5; row++) {
      for (int col = 5; col < 7; col++) {
        frame[row][col] = 1;
      }
    }
    matrix.renderBitmap(frame, 8, 12);
    delay(150);
    
    clearFrame();
    matrix.renderBitmap(frame, 8, 12);
    delay(150);
  }
  delay(300);
}

void loop() {
  unsigned long currentTime = millis();
  
  // Add new lights at current interval
  if (currentTime - lastAddTime >= addInterval) {
    if (lightsAdded < maxLights) {
      addRandomLight();
      lightsAdded++;
      lastAddTime = currentTime;
    } else {
      // All lights added, start erasing sequence
      eraseRowByRow();
      
      // Show cycle indicator
      showCycleIndicator();
      
      // Increase speed for next cycle
      addInterval = max(minInterval, addInterval - speedIncrease);
      
      // Reset for next cycle
      lightsAdded = 0;
      cycleCount++;
      lastAddTime = currentTime;
      
      // Reset speed after 10 cycles to prevent it getting too fast
      if (cycleCount >= 10) {
        cycleCount = 0;
        addInterval = 1000;
      }
    }
  }
  
  // Update display
  matrix.renderBitmap(frame, 8, 12);
  delay(20); // Smoother refresh rate
}
