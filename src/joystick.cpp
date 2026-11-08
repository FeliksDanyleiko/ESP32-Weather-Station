#include <Arduino.h>
#include "joystick.h"

#define JOY_X  1
#define JOY_Y  2
#define JOY_SW 7

bool lastButton = HIGH;
bool stableButton = HIGH;

unsigned long lastDebounce = 0;
unsigned long lastMove = 0;

void initJoystick() {
  pinMode(JOY_SW, INPUT_PULLUP);
  analogReadResolution(12);
}

JoystickAction readJoystick() {
  bool button = digitalRead(JOY_SW);

  if (button != lastButton) {
    lastDebounce = millis();
  }

  lastButton = button;

  if (millis() - lastDebounce > 30 && button != stableButton) {
    stableButton = button;

    if (stableButton == LOW) {
      return PRESS;
    }
  }

  int y = analogRead(JOY_Y);

  if (millis() - lastMove > 250) {
    if (y < 1000) {
      lastMove = millis();
      return UP;
    }
    else if (y > 3000) {
      lastMove = millis();
      return DOWN;
    }
  }

  return NONE;
}
