#pragma once
#include <raylib.h>

typedef struct Animation {
    Rectangle* rectangles;
    int frameCount;
    int frameSpeed;
} Animation;

typedef struct Content {
    Animation playerIdleAnimation;
    Animation playerMoveAnimation;
} Content;

Content* LoadContent();
void UnloadContent(Content* content);
