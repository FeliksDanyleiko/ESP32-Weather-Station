#include <Arduino.h>
#include "display.h"
#include "joystick.h"
#include "sensor.h"

// Current menu selection and screen state
int selected = 0;
bool inMenu = true;
bool inCalibration = false;
bool sensorReady = false;

// Reference pressure used to calculate elevation
float seaLevelPressure = 1013.25f;

// Time of the last sensor update
unsigned long lastUpdate = 0;

// Read the selected measurement and show it
void showPage() {
  float value = 0;

  if (sensorReady) {
    value = readSensorValue(selected, seaLevelPressure);
  }

  drawPage(selected, sensorReady, value);
}

void setup() {
  Serial.begin(115200);
  initJoystick();
  sensorReady = initSensor();
  initDisplay();

  drawMenu(selected);
}

void loop() {
  // Check the joystick without blocking the loop
  JoystickAction action = readJoystick();

  if (inMenu) {
    if (action == UP) {
      // Move up and wrap around to the last item
      selected = (selected + 3) % 4;
      drawMenu(selected);
    }
    else if (action == DOWN) {
      // Move down and wrap around to the first item
      selected = (selected + 1) % 4;
      drawMenu(selected);
    }
    else if (action == PRESS) {
      inMenu = false;
      if (selected == 3) {
        // Set sea-level pressure before showing elevation
        inCalibration = true;
        drawCalibration(seaLevelPressure);
      }
      else {
        showPage();
        lastUpdate = millis();
      }
    }
  }
  else if (inCalibration) {
    if (action == UP) {
      // Increase reference pressure within safe limits
      seaLevelPressure += 0.5f;
      seaLevelPressure = constrain(seaLevelPressure, 850.0f, 1100.0f);
      drawCalibration(seaLevelPressure);
    }
    else if (action == DOWN) {
      // Decrease reference pressure within safe limits
      seaLevelPressure -= 0.5f;
      seaLevelPressure = constrain(seaLevelPressure, 850.0f, 1100.0f);
      drawCalibration(seaLevelPressure);
    }
    else if (action == PRESS) {
      // Confirm calibration and open the elevation page
      inCalibration = false;
      showPage();
      lastUpdate = millis();
    }
  }
  else {
    if (action == PRESS) {
      // Return to the main menu
      inMenu = true;
      drawMenu(selected);
    }

    // Refresh sensor readings every second without delay()
    if (!inMenu && millis() - lastUpdate >= 1000) {
      showPage();
      lastUpdate = millis();
    }
  }
}
