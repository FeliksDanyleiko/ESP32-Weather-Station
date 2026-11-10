#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <math.h>
#include "sensor.h"

Adafruit_BMP280 bmp;

bool initSensor() {
  // Start I2C using GPIO8 (SDA) and GPIO9 (SCL)
  Wire.begin(8, 9);

  // Find the BMP280 at I2C address 0x76
  bool sensorReady = bmp.begin(0x76);

  return sensorReady;
}

float readSensorValue(int selected, float seaLevelPressure) {
  // Read temperature directly in degrees Celsius
  if (selected == 2) {
    return bmp.readTemperature();
  }

  // Convert pressure from pascals to hPa (equal to mbar)
  float pressure = bmp.readPressure() / 100.0f;
  if (selected == 3) {
    // Estimate elevation from current and sea-level pressure
    return 44330.0f *
           (1.0f - powf(pressure / seaLevelPressure, 0.1903f));
  }

  return pressure;
}
