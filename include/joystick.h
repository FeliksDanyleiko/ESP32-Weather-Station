#pragma once

// Possible joystick events
enum JoystickAction {
    NONE,
    UP,
    DOWN,
    PRESS
};

void initJoystick();
JoystickAction readJoystick();
