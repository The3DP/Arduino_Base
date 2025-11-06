///////////////////////////
// The3DP                //
// matrix_effect_row.ino //
// November 6, 2025      //
///////////////////////////

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Define frames as 1D arrays (96 elements each: 8 rows × 12 columns)
const uint32_t frame0[] = {
  0b111111000000,
  0b100000100000,
  0b010000010000,
  0b001000001000,
  0b001000001000,
  0b010000010000,
  0b100000100000,
  0b111111000000
};

const uint32_t frame1[] = {
  0b111111000000,
  0b100000100000,
  0b010000010000,
  0b001010001000,
  0b001001001000,
  0b010000010000,
  0b100000100000,
  0b111111000000
};

const uint32_t frame2[] = {
  0b111111000000,
  0b100000100000,
  0b010101010000,
  0b001010001000,
  0b001000001000,
  0b010101010000,
  0b100000100000,
  0b111111000000
};

const uint32_t frame3[] = {
  0b111111000000,
  0b100000100000,
  0b010101010000,
  0b001101101000,
  0b001010101000,
  0b010101010000,
  0b100000100000,
  0b111111000000
};

// Array of frame pointers
const uint32_t* frames[] = {frame0, frame1, frame2, frame3};
const int numFrames = 4;
int currentFrame = 0;

void eraseEffect() {
  // Gradually turn off LEDs row by row for a simple “erasing” look
  for (int i = 0; i < 8; i++) {
    uint32_t tempFrame[8];
    for (int r = 0; r < 8; r++) {
      if (r < i)
        tempFrame[r] = 0;  // turn off earlier rows
      else
        tempFrame[r] = frames[currentFrame][r];
    }
    matrix.loadFrame(tempFrame);
    delay(80);  // speed of erasing
  }
}

void setup() {
  matrix.begin();
}

void loop() {
  // Display the current frame
  matrix.loadFrame(frames[currentFrame]);
  delay(300);

  // Erase effect before switching
  eraseEffect();

  // Next frame
  currentFrame++;
  if (currentFrame >= numFrames) currentFrame = 0;
}
