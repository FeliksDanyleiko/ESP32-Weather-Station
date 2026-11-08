#pragma once

enum JoystickAction {
    NONE,
    UP,
    DOWN,
    PRESS
};

void initJoystick();
JoystickAction readJoystick();
