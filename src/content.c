#include <stdlib.h>
#include <assert.h>
#include <raylib.h>
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
    content->playerIdleAnimation.rectangles[0] = (Rectangle){ 0.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[1] = (Rectangle){ 24.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[2] = (Rectangle){ 48.0f, 0.0f, 18.0f, 24.0f };
    content->playerIdleAnimation.rectangles[3] = (Rectangle){ 72.0f, 0.0f, 18.0f, 24.0f };

    content->playerMoveAnimation = AllocateAnimation(frameCount, frameSpeed);
    content->playerMoveAnimation.rectangles[0] = (Rectangle){ 0.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[1] = (Rectangle){ 24.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[2] = (Rectangle){ 48.0f, 24.0f, 18.0f, 24.0f };
    content->playerMoveAnimation.rectangles[3] = (Rectangle){ 72.0f, 24.0f, 18.0f, 24.0f };

    content->playerJumpAnimation = AllocateAnimation(frameCount, frameSpeed);
    content->playerJumpAnimation.rectangles[0] = (Rectangle){ 0.0f, 48.0f, 18.0f, 24.0f };
    content->playerJumpAnimation.rectangles[1] = (Rectangle){ 24.0f, 48.0f, 18.0f, 24.0f };
    content->playerJumpAnimation.rectangles[2] = (Rectangle){ 48.0f, 48.0f, 18.0f, 24.0f };
    content->playerJumpAnimation.rectangles[3] = (Rectangle){ 72.0f, 48.0f, 18.0f, 24.0f };

}

static void UnloadPlayerAnimations(Content* content) {
    FreeAnimation(content->playerIdleAnimation);
    FreeAnimation(content->playerMoveAnimation);
    FreeAnimation(content->playerJumpAnimation);
}

Content* LoadContent() {
    Content* content = malloc(sizeof(Content));
    assert(content);

    LoadPlayerAnimations(content);
    if (content) {
        content->playerAtlas = LoadTexture("export/player.png");
    }

    return content;
}

void UnloadContent(Content* content) {
    UnloadPlayerAnimations(content);
    UnloadTexture(content->playerAtlas);
    free(content);
}
