#include <SPI.h>
#include <SD.h>
#include "SenseBoxMCU.h"

File myFile;
HDC1080 hdc;
const char *TEMP_ID = "SENSORID";
const char *HUMI_ID= "SENSORID";

const long interval = 60000; // 60.000 Millisekunden = 60 Sekunden
long time_start = 0;
long time_actual = 0;

void setup() {
  // put your setup code here, to run once:
  SD.begin(28);
  myFile = SD.open("data.csv", FILE_WRITE);
  myFile.close();
}

void loop() {

  time_start = millis();
  if (time_start > time_actual + interval) {
    time_actual = millis();
    myFile = SD.open("data.txt", FILE_WRITE);
    myFile.print(TEMP_ID);
    myFile.print(",");
    myFile.println(hdc.getTemperature());
    // zweiter Messwert
    myFile.print(HUMI_ID);
    myFile.print(",");
    myFile.println(hdc.getHumidity());
    
    myFile.close();
  }

}
