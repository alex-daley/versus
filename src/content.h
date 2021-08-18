#pragma once
#include <raylib.h>
#include "animator.h"

typedef struct Content {
    Texture playerAtlas;
    Animation playerIdleAnimation;
    Animation playerMoveAnimation;
    Animation playerJumpAnimation;
    Animation playerFallAnimation;
    Animation playerWallAnimation;
} Content;

Content* LoadContent();
void UnloadContent(Content* content);
