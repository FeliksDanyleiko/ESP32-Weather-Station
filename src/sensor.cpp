
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "sensor.h"

Adafruit_BMP280 bmp;

bool initSensor() {
  Wire.begin(8, 9);

  bool sensorReady = bmp.begin(0x76);

  if (sensorReady) {
    Serial.println("BMP280 connected");
  } else {
    Serial.println("BMP280 not found");
  }

  return sensorReady;
}

float readSensorValue(int selected) {
  if (selected == 0 || selected == 1) {
    return bmp.readPressure() / 100.0;
  }
  else {
    return bmp.readTemperature();
  }
}
