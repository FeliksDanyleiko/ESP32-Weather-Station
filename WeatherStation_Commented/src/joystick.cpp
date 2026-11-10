#include <Arduino.h>
#include "joystick.h"

// Joystick analogue axes and push-button pin
#define JOY_X  1
#define JOY_Y  2
#define JOY_SW 7

bool lastButton = HIGH;
bool stableButton = HIGH;

unsigned long lastDebounce = 0;
unsigned long lastMove = 0;

void initJoystick() {
  // The button is active-low; use the internal pull-up
  pinMode(JOY_SW, INPUT_PULLUP);
  analogReadResolution(12);
}

JoystickAction readJoystick() {
  bool button = digitalRead(JOY_SW);

  // Start debounce timing when the button level changes
  if (button != lastButton) {
    lastDebounce = millis();
  }

  lastButton = button;

  // Accept one press only after the signal is stable for 30 ms
  if (millis() - lastDebounce > 30 && button != stableButton) {
    stableButton = button;
    if (stableButton == LOW) {
      return PRESS;
    }
  }

  // Read the vertical axis of the joystick
  int y = analogRead(JOY_Y);

  // Limit repeated movements to one every 250 ms
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

  // No new button press or joystick movement
  return NONE;
}
