#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include "sensor.h"

Adafruit_BMP280 bmp;

bool initSensor() {
  Wire.begin(8, 9);

  bool sensorReady = bmp.begin(0x76);

  return sensorReady;
}

float readSensorValue(int selected, float seaLevelPressure) {
  if (selected == 2) {
    return bmp.readTemperature();
  }

  float pressure = bmp.readPressure() / 100.0f;

  if (selected == 3) {
    return 44330.0f *
           (1.0f - powf(pressure / seaLevelPressure, 0.1903f));
  }

  return pressure;
}
