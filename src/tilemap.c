#include <assert.h>
#include "tilemap.h"

static inline int RoundTo(int value, int multiple) {
    return value - value % multiple;
}

void WorldToTilePoint(Tilemap map, float x, float y, int* outX, int* outY) {
    int tileSize = map.tileSize;
    *outX = RoundTo((int)x, tileSize) / tileSize;
    *outY = RoundTo((int)y, tileSize) / tileSize;

    assert(*outX < map.columns);
    assert(*outX >= 0);
    assert(*outY < map.rows);
    assert(*outY >= 0);
}

void TileToWorldPoint(Tilemap map, int x, int y, float* outX, float* outY) {
    assert(x < map.columns);
    assert(x >= 0);
    assert(y < map.rows);
    assert(y >= 0);

    *outX = x * map.tileSize;
    *outY = y * map.tileSize;

}

Tile TileAt(Tilemap map, int x, int y) {
    assert(x < map.columns);
    assert(x >= 0);
    assert(y < map.rows);
    assert(y >= 0);

    return map.tiles[x + map.columns * y];
}
