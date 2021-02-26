#include <iostream>
#include "mahjong.h"

int main() {
    Tile tiles[14] = { TileCode::TILE_1M, TILE_1M, TILE_1M, TILE_2M, TILE_2M, TILE_3M, TILE_3M, TILE_4M, TILE_4P, TILE_6P, TILE_6P, TILE_2S, TILE_DONG, TILE_DONG };
    Hand hand(tiles);
    hand.countXiangting();
    return 0;
}