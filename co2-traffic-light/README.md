# senseBox CO2 Traffic Light

The senseBox CO2 Traffic Light set contains all components to build a CO2 traffic light with CO2 display (in ppm). The CO2 concentration is visualized in three steps for an RGB LED:

green (0 to 999ppm)
yellow (1000 to 1499ppm)
red (from 1500ppm)
The CO2 traffic light can be programmed with Blockly for senseBox. An assembly instruction and a precompiled program code can be found in our [documentation](https://docs.sensebox.de/hardware/sets-co2-ampel/).

## Source Code

The Source Code can be found in this repository. For the Arduino Source code install the [Board Support Package](https://github.com/sensebox/senseBoxMCU-core/tree/master/arduino) and [Sparkfun SCD30 Library](https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library).

- [01_Raw_Data](https://github.com/sensebox/sensebox-examples/tree/main/co2-traffic-light/01_Raw_Data)
- [02_Average](https://github.com/sensebox/sensebox-examples/tree/main/co2-traffic-light/02_Average)

 As an alternative you can use [Blockly for senseBox](https://blockly.sensebox.de/ardublockly/?board=sensebox-mcu) without any software installation in your browser!

- [01_Raw_Data](https://blockly.sensebox.de/ardublockly/index.html?board=sensebox-mcu&gallery=projects/co2_traffic_light_raw)
- [02_Average](https://blockly.sensebox.de/ardublockly/index.html?board=sensebox-mcu&gallery=projects/co2_traffic_light_avg)

## Technical details
- senseBox MCU lite
- senseBox WS2812 RGB LED
- senseBox CO2 Sensor (Sensirion SCD30)
- senseBox OLED
- laser-cut acrylic housing
- 5m USB Cable
- USB Power Supply

Get your [senseBox CO2 Traffic light](https://sensebox.shop/product/co2-ampel-bausatz) in our [Shop](https://sensebox.shop/product/co2-ampel-bausatz)