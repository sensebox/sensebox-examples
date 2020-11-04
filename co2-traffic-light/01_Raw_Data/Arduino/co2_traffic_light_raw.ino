/*
Display raw values from SCD30 sensor
co2, temp, humi
with senseBox MCU, SCD30(I2C), OLED-Display (I2C), RGB LED (digital A)
*/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_SCD30_Arduino_Library.h> 

SCD30 airSensor;
uint16_t co2;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_NeoPixel rgb_led_1 = Adafruit_NeoPixel(1,1,NEO_RGB + NEO_KHZ800);

void setup()
{
  delay(2000);
  //The SCD30 has data ready every two seconds
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.setTextSize(2);
  display.setTextColor(WHITE,BLACK);
  display.display();
  delay(3000);
  display.clearDisplay();

  if (airSensor.begin() == false)
  {
    //Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    display.print("CO2 sensor error");
    display.display();
    while (1)
      ;
  } 
  rgb_led_1.begin();
}

void loop()
{
  if (airSensor.dataAvailable())
  {
    co2 = airSensor.getCO2();
    delay(10);

    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0,16);
    display.println(co2);
    display.setTextSize(2);
    display.setCursor(0,45);
    display.println("ppm");

    display.display();
  }
  else
  {
    display.setTextSize(2);
    display.print("CO2 sensor error in loop");
    display.display();
  }

  if(co2 > 0 && co2 <= 1000) {
    rgb_led_1.setPixelColor(0,rgb_led_1.Color(200,0,0));
    rgb_led_1.show();    
  }
  else if(co2 > 1000 && co2 <= 1500) {
    rgb_led_1.setPixelColor(0,rgb_led_1.Color(100,200,0));
    rgb_led_1.show();
  }
  else if(co2 > 1500) {
    rgb_led_1.setPixelColor(0,rgb_led_1.Color(0,200,0));
    rgb_led_1.show();
  }
  delay(2000);
}
