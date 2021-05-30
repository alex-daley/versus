#include <stdlib.h>
#include <assert.h>
#include "content.h"
#include "tilegrid_serialisation.h"

Content* LoadContent()
{
    Content* content = malloc(sizeof(Content));
    assert(content);

    content->atlas = LoadTexture("export/atlas.png");
    content->solidTile = (Rectangle){ 0, 0, 16, 16 };
    content->tileGrid = LoadTileGrid("./level.txt");

    return content;
}

void UnloadContent(Content* content)
{
    UnloadTexture(content->atlas);
    UnloadTileGrid(&content->tileGrid);
    free(content);
}
