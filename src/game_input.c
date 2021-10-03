#include "game_input.h"
#include <raylib.h>
#include <math.h>

static const float gamepadDeadzone = 0.1f;
static const int gamepadJumpButton = GAMEPAD_BUTTON_RIGHT_FACE_DOWN;
static const int gamepadShootButton = GAMEPAD_BUTTON_RIGHT_FACE_LEFT; 
static const int gamepadMoveAxis = GAMEPAD_AXIS_LEFT_X;
static const int keyboardJumpKey = KEY_SPACE;
static const int keyboardMoveLeftKey = KEY_A;
static const int keyboardMoveRightKey = KEY_D;
static const int keyboardShootKey = KEY_K;

static bool OutsideGamepadDeadzone(float axisValue) {
    return fabs(axisValue) > gamepadDeadzone;
}

static bool AnyInput(InputState input) {
    return input.x != 0 || input.jump != JUMP_BUTTON_UP || input.shoot;
}

static InputState GetGamepadInput(int gamepadIndex) {
    InputState input = { 0 };

    const float x = GetGamepadAxisMovement(gamepadIndex, gamepadMoveAxis);
    if (OutsideGamepadDeadzone(x)) {
        input.x = (int)roundf(x);
    }
    else {
        input.x = 0;
    }

    if (IsGamepadButtonPressed(gamepadIndex, gamepadJumpButton)) {
        input.jump = JUMP_BUTTON_PRESSED;
    }
    else if (IsGamepadButtonDown(gamepadIndex, gamepadJumpButton)) {
        input.jump = JUMP_BUTTON_DOWN;
    }
    else if (IsGamepadButtonReleased(gamepadIndex, gamepadJumpButton)) {
        input.jump = JUMP_BUTTON_RELEASED;
    }
    else {
        input.jump = JUMP_BUTTON_UP;
    }
    
    input.shoot = IsGamepadButtonPressed(gamepadIndex, gamepadShootButton);

    return input;
}

static InputState GetKeyboardInput() {
    InputState input = { 0 };

    if (IsKeyDown(keyboardMoveRightKey)) {
        input.x += 1;
    }
    if (IsKeyDown(keyboardMoveLeftKey)) {
        input.x -= 1;
    }

    if (IsKeyPressed(keyboardJumpKey)) {
        input.jump = JUMP_BUTTON_PRESSED;
    }
    else if (IsKeyDown(keyboardJumpKey)) {
        input.jump = JUMP_BUTTON_DOWN;
    }
    else if (IsKeyReleased(keyboardJumpKey)) {
        input.jump = JUMP_BUTTON_RELEASED;
    }
    else {
        input.jump = JUMP_BUTTON_UP;
    }

    input.shoot = IsKeyPressed(keyboardShootKey);

    return input;
}

InputState GetInput(int playerIndex) {
    InputState input = GetGamepadInput(playerIndex);
    
    // Player 1 can optionally use a keyboard.
    if (playerIndex == 0 && !AnyInput(input)) {
        input = GetKeyboardInput();
    }

    return input;
}
