#include <stdlib.h>
#include <assert.h>
#include <raylib.h>
#include "tilemap_serialisation.h"

static const int columns = 20;
static const int rows = 15;
static const int tileSize = 16;

static inline size_t GetTileCount() {
    return (size_t)columns * rows;
}

static inline bool IsTile(int id) {
    return id == 0 || id == 1;
}

static inline int ToInt(char c) {
    return (int)c - '0';
}

static inline char ToChar(int i) {
    return (char)i + '0';
}

static Tilemap AllocateTilemap() {
    Tilemap map = { 0 };
    map.tileSize = tileSize;
    map.columns = columns;
    map.rows = rows;
    map.tiles = calloc(GetTileCount(), sizeof(Tile));
    return map;
}

Tilemap LoadTilemap(const char* fileName) {
    Tilemap map = AllocateTilemap();

    if (!FileExists(fileName)) {
        TraceLog(LOG_WARNING, "%s not found", fileName);
        return map;
    }

    char* text = LoadFileText(fileName);
    for (size_t i = 0; i < GetTileCount(); i++) {
        Tile tile = (Tile)ToInt(text[i]);

        if (!IsTile(tile)) {
            TraceLog(LOG_WARNING, "Unknown tile id: %c at position %i in file %s", text[i], i, fileName);
            UnloadTilemap(map);
            UnloadFileText(text);

            return AllocateTilemap();
        }

        map.tiles[i] = tile;
    }

    UnloadFileText(text);

    return map;
}

void UnloadTilemap(Tilemap map) {
    free(map.tiles);
}

void WriteTilemap(Tilemap map, const char* fileName) {
    if (!fileName) {
        TraceLog(LOG_WARNING, "Not saving tile map because fileName was null");
        return;
    }

    char* buffer = malloc((GetTileCount() + 1) * sizeof(char));

    assert(buffer);

    #pragma warning(push)
    #pragma warning(disable : 6386)

    // DANGER ZONE
    for (size_t i = 0; i < GetTileCount(); ++i) {
        buffer[i] = ToChar(map.tiles[i]);
    }

    buffer[GetTileCount()] = '\0';

    #pragma warning( pop )

    SaveFileText(fileName, buffer);
    free(buffer);
}
