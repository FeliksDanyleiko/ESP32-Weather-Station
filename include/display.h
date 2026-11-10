#pragma once

// TFT initialisation and screen drawing functions
void initDisplay();
void drawMenu(int selected);
void drawPage(int selected, bool sensorReady, float value);
void drawCalibration(float seaLevelPressure);
