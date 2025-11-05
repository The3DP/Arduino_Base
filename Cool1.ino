#include <Wire.

void loop() {
  // === LCD Typewriter Animation ===
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int i = 0; i < line1.length(); i++) {
    lcd.print(line1[i]);
    delay(150);
  }

  delay(300);

  lcd.setCursor(0, 1);
  for (int i = 0; i < line2.length(); i++) {
    lcd.print(line2[i]);
    delay(150);
  }

  delay(2000);

  // LCD wipe out animation
  for (int i = 15; i >= 0; i--) {
    lcd.setCursor(i, 0);
    lcd.print(" ");
    lcd.setCursor(i, 1);
    lcd.print(" ");
    delay(50);
  }

  delay(500);

  // === Matrix Text Scroll ===
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(75);
  matrix.textFont(Font_4x6);
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(message);
  matrix.endText(SCROLL_LEFT);
  matrix.endDraw();
  
  delay(4000); // Let message scroll completely
}