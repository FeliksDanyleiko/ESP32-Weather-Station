
#include <Arduino.h>
#include "display.h"
#include "joystick.h"
#include "sensor.h"

int selected = 0;
bool inMenu = true;
bool sensorReady = false;

unsigned long lastMove = 0;
unsigned long lastUpdate = 0;

void showPage() {
  float value = 0;

  if (sensorReady) {
    value = readSensorValue(selected);
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
  int y = readJoystickY();

  if (inMenu && millis() - lastMove > 250) {
    if (y < 1000) {
      selected = (selected + 2) % 3;
      drawMenu(selected);
      lastMove = millis();
    }
    else if (y > 3000) {
      selected = (selected + 1) % 3;
      drawMenu(selected);
      lastMove = millis();
    }
  }

  if (joystickPressed()) {
    inMenu = !inMenu;

    if (inMenu) {
      drawMenu(selected);
    } else {
      showPage();
      lastUpdate = millis();
    }
  }

  if (!inMenu && millis() - lastUpdate >= 1000) {
    showPage();
    lastUpdate = millis();
  }
}
