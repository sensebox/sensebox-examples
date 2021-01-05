#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#include "SenseBoxMCU.h"
Adafruit_SSD1306 display(OLED_RESET);
Button switchButton(0);
int page = 0;
void setup()
{
  senseBoxIO.powerI2C(true);
  delay(2000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.display();
  delay(100);
  display.clearDisplay();
  switchButton.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (switchButton.isPressed()) {
    if (page == 3) {
      page = 0;
    }
    else {
      page += 1;
    }
  }
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  switch (page)
  {
    case 0:
      display.println("Seite 1");
      break;
    case 1:
      display.println("Seite 2");
      break;
    case 2:
      display.println("Seite 3");
      break;
    case 3:
      display.println("Seite 4");
      break;
  }
  display.display();
}
