#include <Arduino.h>
#include <U8g2lib.h>
#include "Motor.h"

Motor motor(22, 24, 28, 26, 30, 32, 36, 34, 2, 3, 4, 5);

// Adjust these settings based on your specific OLED module.
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);

int cur_speed = 200;

void setup() {
  u8g2.begin();
  motor.speed(cur_speed);
}

void loop() {
  Display_speed();
  motor.forward();
  Display_direction_right();
  Display_direction_left();
}

void Display_speed() {
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  String message = "Current speed:  " + String(cur_speed);
  u8g2.drawStr(0, 10, message.c_str());  // write something to the internal memory
  u8g2.sendBuffer();                     // transfer internal memory to the display
}
void Display_direction_right() {
  // Draw an right-facing arrow.
  // You may need to adjust these coordinates based on your display and preferences.
  u8g2.drawLine(30, 30, 90, 30);  // Horizontal line
  u8g2.drawLine(70, 20, 90, 30);  // Upper diagonal line
  u8g2.drawLine(70, 40, 90, 30);  // Lower diagonal line

  u8g2.sendBuffer();  // transfer internal memory to the display
}
void Display_direction_left() {
  // Draw a left-facing arrow.
  // You may need to adjust these coordinates based on your display and preferences.
  u8g2.drawLine(90, 30, 30, 30);  // Horizontal line
  u8g2.drawLine(50, 20, 30, 30);  // Upper diagonal line
  u8g2.drawLine(50, 40, 30, 30);  // Lower diagonal line
  u8g2.sendBuffer();              // transfer internal memory to the display
}
