/*
Display average values from SCD30 sensor
co2, temp, humi
with senseBox MCU, SCD30(I2C), OLED-Display (I2C), RGB LED (digital A)
*/

#include <SPI.h>
#include <Wire.h>
#include <senseBoxIO.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <SparkFun_SCD30_Arduino_Library.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

SCD30 airSensor;
uint16_t scd30_co2;
int n = 6; //6 times per minute = measurement every 10 secs. Attention: sensor readings at 0.5Hz max!

Adafruit_NeoPixel rgb_led_1 = Adafruit_NeoPixel(1, 1, NEO_RGB + NEO_KHZ800);

void setup() {
  senseBoxIO.powerI2C(true);
  delay(2000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  display.display();
  delay(1000);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  delay(1000);
  
  Wire.begin();
  if (airSensor.begin() == false)
  {
    display.println("Sensor error.");
    display.display();
    while (1); //do not continue
  }
  else {
    display.println("Sensor ok");
    display.setTextSize(1);
    display.println("Wait 60 sec for first measurment");
    display.display();
  }
  rgb_led_1.begin();
}

void loop() {
  //Calculate average each min from n iterations
  int counter = 0; // real number of measurements
  int co2_sum = 0; // summed up measurements
  for (int steps = 0; steps < n; steps++) {
    if (airSensor.dataAvailable())
    {
      scd30_co2 = airSensor.getCO2();
      co2_sum += scd30_co2;
      counter++;
    }
    delay(int(60000 / n));
  }
  unsigned int co2_avg = co2_sum / counter;

  // Anzeigen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.println(co2_avg);
  display.setCursor(0, 28);
  display.setTextSize(2);
  display.println("ppm");
  display.display();

  if (co2_avg > 0 && co2_avg <= 1000) {
    rgb_led_1.setPixelColor(0, rgb_led_1.Color(200, 0, 0));
    rgb_led_1.show();
  }
  else if (co2_avg > 1000 && co2_avg <= 1500) {
    rgb_led_1.setPixelColor(0, rgb_led_1.Color(100, 200, 0));
    rgb_led_1.show();
  }
  else if (co2_avg > 1500) {
    rgb_led_1.setPixelColor(0, rgb_led_1.Color(0, 200, 0));
    rgb_led_1.show();
  }
}
