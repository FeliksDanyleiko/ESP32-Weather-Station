
#include <Arduino.h>
#include "joystick.h"

#define JOY_X  1
#define JOY_Y  2
#define JOY_SW 7

bool lastButton = HIGH;

void initJoystick() {
  pinMode(JOY_SW, INPUT_PULLUP);
  analogReadResolution(12);
}

int readJoystickY() {
  return analogRead(JOY_Y);
}

bool joystickPressed() {
  bool button = digitalRead(JOY_SW);

  bool pressed = (lastButton == HIGH && button == LOW);

  lastButton = button;

  return pressed;
}
