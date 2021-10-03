#pragma once
#include <stdbool.h>

typedef enum JumpButton {
    JUMP_BUTTON_PRESSED,
    JUMP_BUTTON_DOWN,
    JUMP_BUTTON_RELEASED,
    JUMP_BUTTON_UP
} JumpButton;

typedef struct InputState {
    JumpButton jump;
    bool shoot;
    int x;
} InputState;

InputState GetInput(int playerIndex);
