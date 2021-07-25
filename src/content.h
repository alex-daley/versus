#pragma once
#include <raylib.h>
#include "animator.h"

typedef struct Content {
    Texture playerAtlas;
    Animation playerIdleAnimation;
    Animation playerMoveAnimation;
    Animation playerJumpAnimation;
} Content;

Content* LoadContent();
void UnloadContent(Content* content);
