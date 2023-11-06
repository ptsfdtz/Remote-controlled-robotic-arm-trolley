#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/SCL, /* data=*/SDA, /* reset=*/U8X8_PIN_NONE);

class Screen {
private:

public:
  int cur_speed = 0;
  Screen() {
  }

  void Display_speed() {
    u8g2.clearBuffer();                  // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
    String message = "Current speed: " + String(cur_speed);
    u8g2.drawStr(0, 10, message.c_str());
    u8g2.sendBuffer();  // transfer internal memory to the display
  }

  void Display_direction() {
    u8g2.clearBuffer();                  // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
    String message = "Current direction: ";
    u8g2.drawStr(0, 10, message.c_str());
    u8g2.sendBuffer();  // transfer internal memory to the display
  }
};