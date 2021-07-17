#include <stdlib.h>
#include <assert.h>
#include "content.h"

static Animation AllocateAnimation(int frameCount, int frameSpeed) {
    Animation animation = { 0 };
    animation.rectangles = malloc(sizeof(Rectangle) * frameCount);
    animation.frameCount = frameCount;
    animation.frameSpeed = frameSpeed;
    assert(animation.rectangles);
    return animation;
}

static void FreeAnimation(Animation animation) {
    free(animation.rectangles);
}

static void LoadPlayerAnimations(Content* content) {
    const int frameCount = 4;
    const int frameSpeed = 8;

    content->playerIdleAnimation = AllocateAnimation(frameCount, frameSpeed);
    content->playerIdleAnimation.rectangles[0] = (Rectangle){  0.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[1] = (Rectangle){ 24.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[2] = (Rectangle){ 48.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[3] = (Rectangle){ 72.0f, 0.0f, 18.0f, 24.0f };

    content->playerMoveAnimation = AllocateAnimation(frameCount, frameSpeed);
    content->playerMoveAnimation.rectangles[0] = (Rectangle){  0.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[1] = (Rectangle){ 24.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[2] = (Rectangle){ 48.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[3] = (Rectangle){ 72.0f, 24.0f, 18.0f, 24.0f };
}

static void UnloadPlayerAnimations(Content* content) {
    FreeAnimation(content->playerIdleAnimation);
    FreeAnimation(content->playerMoveAnimation);
}

Content* LoadContent() {
    Content* content = malloc(sizeof(Content));
    assert(content);
    LoadPlayerAnimations(content);

    return content;
}

void UnloadContent(Content* content) {
    UnloadPlayerAnimations(content);
    free(content);
}
