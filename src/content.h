#ifndef VERSUS_CONTENT_H
#define VERSUS_CONTENT_H
#include <raylib.h>

typedef struct Content
{
    Texture2D atlas;
    Rectangle solidTile;
} Content;

Content* LoadContent();
void UnloadContent(Content* content);

#endif
