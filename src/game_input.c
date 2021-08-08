#include "game_input.h"
#include <raylib.h>
#include <math.h>

static const float deadzone = 0.1f;

static bool OutsideDeadzone(float value, float deadzone) {
    return fabs(value) > deadzone;
}

static InputState AddGamepadInput(InputState input, int index) {
    float axisX = GetGamepadAxisMovement(index, GAMEPAD_AXIS_LEFT_X);
    
    if (OutsideDeadzone(axisX, deadzone)) {
        input.x = (int)roundf(axisX);
    }
    else {
        input.x = 0;
    }

    const int jumpButton = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
    if (IsGamepadButtonPressed(index, jumpButton)) {
        input.jump = JUMP_BUTTON_PRESSED;
    }
    else if (IsGamepadButtonDown(index, jumpButton)) {
        input.jump = JUMP_BUTTON_DOWN;
    }
    else if (IsGamepadButtonReleased(index, jumpButton)) {
        input.jump = JUMP_BUTTON_RELEASED;
    }
    else {
        input.jump = JUMP_BUTTON_UP;
    }

    return input;
}

static InputState AddKeyboardInput(InputState input) {
    
    int x = 0;
    if (IsKeyDown(KEY_A)) x -= 1;
    if (IsKeyDown(KEY_D)) x += 1;
    input.x = x;

    if (IsKeyPressed(KEY_SPACE)) {
        input.jump = JUMP_BUTTON_PRESSED;
    }
    else if (IsKeyDown(KEY_SPACE)) {
        input.jump = JUMP_BUTTON_DOWN;
    }
    else if (IsKeyReleased(KEY_SPACE)) {
        input.jump = JUMP_BUTTON_RELEASED;
    }
    else {
        input.jump = JUMP_BUTTON_UP;
    }

    return input;
}

InputState GetInput() {
    const int controllerIndex = 0;

    InputState input = { 0 };
    input = AddGamepadInput(input, controllerIndex);

    if (input.x == 0 && input.jump == JUMP_BUTTON_UP) {
        input = AddKeyboardInput(input);
    }

    return input;
}
