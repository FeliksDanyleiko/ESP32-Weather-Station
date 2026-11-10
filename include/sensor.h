#pragma once

// BMP280 initialisation and measurement functions
bool initSensor();
float readSensorValue(int selected, float seaLevelPressure);
