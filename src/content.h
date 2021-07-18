#pragma once
#include <raylib.h>
#include "animator.h"

typedef struct Content {
    Texture playerAtlas;
    Animation playerIdleAnimation;
    Animation playerMoveAnimation;
} Content;

Content* LoadContent();
void UnloadContent(Content* content);
