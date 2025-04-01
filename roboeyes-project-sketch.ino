#include <Wire.h>
#include <Adafruit_GFX.h> // http://librarymanager/All#Adafruit_GFX_Library
#include <Adafruit_SSD1306.h> // http://librarymanager/All#Adafruit_SSD1306
#include <vl53l8cx.h>

VL53L8CX sensor_vl53l8cx(&Wire, -1, -1);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <FluxGarage_RoboEyes.h>
roboEyes roboEyes; // create RoboEyes instance

long update_interval = 75;
long start_time = 0;
long actual_time = 0;

void setup() {
  Serial.begin(9600);

  delay(1000);

  //Starten des ToF-Sensor
  Wire.begin();
  Wire.setClock(1000000); //Sensor has max I2C freq of 1MHz
  sensor_vl53l8cx.begin();
  sensor_vl53l8cx.init();
  sensor_vl53l8cx.set_ranging_frequency_hz(30);
  sensor_vl53l8cx.set_resolution(VL53L8CX_RESOLUTION_8X8);
  sensor_vl53l8cx.start_ranging();
  Wire.setClock(100000); //Sensor has max I2C freq of 1MHz

  // Starten des OLED Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3C or 0x3D
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Starten der RoboEyes
  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100); // Bildschirmweite, Bildschirmhöhe, maximale Framerate

  roboEyes.setAutoblinker(ON, 3, 2); // Blinzelt in einem Intervall von (3) Sekunden mit einer Variation von (2) Sekunden
}


void loop() {

  start_time = millis();
  if (start_time > actual_time + update_interval) {
    actual_time = millis();

    //Auslesen der Messdaten des ToF-Distanzsensors
    VL53L8CX_ResultsData Result;
    uint8_t NewDataReady = 0;
    uint8_t status;

    Wire.setClock(1000000); //Sensor has max I2C freq of 1MHz
    status = sensor_vl53l8cx.check_data_ready(&NewDataReady);
    Wire.setClock(100000); //Sensor has max I2C freq of 1MHz

    if ((!status) && (NewDataReady != 0)) {
      Wire.setClock(1000000); //Sensor has max I2C freq of 1MHz
      sensor_vl53l8cx.get_ranging_data(&Result);
      Wire.setClock(100000); //Sensor has max I2C freq of 1MHz

      // Finden des Pixels mit der geringsten Distanz
      int min_index = 0;
      uint16_t min_distance = (long)(&Result)->distance_mm[0];
      for (int i = 1; i < 64; i++) {
        if ((long)(&Result)->distance_mm[i] < min_distance) {
          min_distance = (long)(&Result)->distance_mm[i];
          min_index = i;
        }
      }

      // Übersetzung der Pixelnummer in eine Blickrichtung der RoboEyes
      if (min_distance < 400) {
        int row = min_index / 8;
        int col = min_index % 8;

        unsigned char direction;

        if (row == 3 || row == 4) {
          if (col == 3 || col == 4) {
              direction = DEFAULT;
          } else if (col < 3) {
              direction = W;
          } else {
              direction = E;
          }
        } else if (row < 3) {
          if (col == 3 || col == 4) {
              direction = S;
          } else if (col < 3) {
              direction = SW;
          } else {
              direction = SE;
          }
        } else {
          if (col == 3 || col == 4) {
              direction = N;
          } else if (col < 3) {
              direction = NW;
          } else {
              direction = NE;
          }
        }
        
        roboEyes.setPosition(direction);

      }

      //Festlegen der Stimmung je nach gemessener Distanz
      if (min_distance < 120) {
        roboEyes.setMood(HAPPY);
      } else if (min_distance < 400) {
        roboEyes.setMood(DEFAULT);
      } else {
        roboEyes.setMood(TIRED);
      }
    }
  }
  
  // Aktualisieren der Augen
  roboEyes.update();  

}