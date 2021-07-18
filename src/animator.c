#include "animator.h"
#include "config.h"

void UpdateAnimator(Animator* animator, Animation animation) {
    int frameCounter = animator->frameCounter;
    int currentFrame = animator->currentFrame;

    if (++frameCounter >= (targetFPS / (double)animation.frameSpeed)) {
        frameCounter = 0;
    
        if (++currentFrame >= animation.frameCount) {
            currentFrame = 0;
        }
    }

    animator->frameCounter = frameCounter;
    animator->currentFrame = currentFrame;
}
