//////////////////////
//     The3DP       //
//Hourglass program //
// Date: 11/6/2025  //
//////////////////////

//////////////////////
//     The3DP       //
//Hourglass program //
// Date: 11/3/2025  //
//////////////////////

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

// Define frames (8 rows × 12 columns)
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

// Array of frames
const uint32_t* frames[] = {frame0, frame1, frame2, frame3};
const int numFrames = 4;
int currentFrame = 0;

// Dimensions of matrix
const int ROWS = 8;
const int COLS = 12;

// Random pixel erase effect
void eraseEffectRandom(const uint32_t* frame) {
  // Copy the current frame into a temporary buffer
  uint32_t tempFrame[ROWS];
  for (int r = 0; r < ROWS; r++) {
    tempFrame[r] = frame[r];
  }

  // Create an array of all pixel coordinates
  int totalPixels = ROWS * COLS;
  int coords[totalPixels];
  for (int i = 0; i < totalPixels; i++) coords[i] = i;

  // Shuffle pixels randomly
  for (int i = 0; i < totalPixels; i++) {
    int j = random(totalPixels);
    int temp = coords[i];
    coords[i] = coords[j];
    coords[j] = temp;
  }

  // Gradually turn off pixels in random order
  for (int k = 0; k < totalPixels; k++) {
    int index = coords[k];
    int r = index / COLS;
    int c = index % COLS;

    // Turn off bit c in row r
    tempFrame[r] &= ~(1 << (COLS - 1 - c));
    matrix.loadFrame(tempFrame);
    delay(10);  // smaller = faster erase
  }
}

void setup() {
  matrix.begin();
  randomSeed(analogRead(A0));  // seed randomness
}

void loop() {
  matrix.loadFrame(frames[currentFrame]);
  delay(400);

  eraseEffectRandom(frames[currentFrame]);

  currentFrame++;
  if (currentFrame >= numFrames) currentFrame = 0;
}
