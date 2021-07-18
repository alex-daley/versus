#pragma once
#include <raylib.h>

typedef struct Animation {
    Rectangle* rectangles;
    int frameCount;
    int frameSpeed;
} Animation;

typedef struct Animator {
    int currentFrame;
    int frameCounter;
    bool flipX;
} Animator;

void UpdateAnimator(Animator* animator, Animation animation);
