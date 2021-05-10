#include <stdlib.h>
#include <assert.h>
#include "content.h"

Content* LoadContent()
{
    Content* content = malloc(sizeof(Content));
    assert(content);

    content->atlas = LoadTexture("export/atlas.png");
    content->solidTile = (Rectangle){ 0, 0, 16, 16 };

    return content;
}

void UnloadContent(Content* content)
{
    free(content);
}
