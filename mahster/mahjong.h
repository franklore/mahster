#pragma once
#include <algorithm>
#include <vector>
#include <string>
////////////////
// Tile
////////////////
 
enum TileCode {
    TILE_EMPTY, 
    TILE_1M, TILE_2M, TILE_3M, TILE_4M, TILE_5M, TILE_6M, TILE_7M, TILE_8M, TILE_9M,
    TILE_1P, TILE_2P, TILE_3P, TILE_4P, TILE_5P, TILE_6P, TILE_7P, TILE_8P, TILE_9P,
    TILE_1S, TILE_2S, TILE_3S, TILE_4S, TILE_5S, TILE_6S, TILE_7S, TILE_8S, TILE_9S,
    TILE_DONG, TILE_NAN, TILE_XI, TILE_BEI, TILE_ZHONG, TILE_FA, TILE_BAI,
};

enum TileSuit {
    WAN, TONG, SUO, ZI
};

std::string TileName[34] = {
    "一", "二", "三", "四", "五", "六", "七", "八", "九",
    "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "①", "②", "③", "④", "⑤", "⑥", "⑦", "⑧", "⑨",
    "东", "南", "西", "北", "中", "发", "白",
};

class Tile {
private:
    TileCode tileCode;

public:
    Tile(TileCode code) : tileCode(code) {

    }

    inline int getNum() const {
        return tileCode % 9;
    }

    inline TileSuit getSuit() const {
        return (TileSuit)((tileCode - 1) / 9);
    }

    inline TileCode getTileCode() const {
        return tileCode;
    }

};

inline bool compareTile(const Tile &a, const Tile &b) {
    return a.getTileCode() > b.getTileCode();
}


///////////////
//Group
///////////////

class Group {
private:
    Tile* tile[3];
public:
    bool addTile(Tile* t) {
        if (tile[0] == nullptr) {
            tile[0] = t;
            return true;
        }
        else if (tile[1] == nullptr) {
            if (tile[0]->getSuit() == t->getSuit() && std::abs(tile[0]->getNum() - t->getNum()) <= 2) {
                if (tile[0]->getNum() > t->getNum()) {
                    tile[1] = tile[0];
                    tile[0] = t;
                }
                else {
                    tile[1] = t;
                }
                return true;
            }
            else {
                return false;
            }
        }
        else if (tile[2] == nullptr) {
            if (tile[0]->getNum() == tile[1]->getNum() &&
                tile[0]->getNum() == t->getNum()) {
                tile[2] = t;
                return true;
            }
            else if (tile[0]->getNum() + 1 == tile[1]->getNum()) {
                if (t->getNum() == tile[0]->getNum() - 1) {
                    tile[2] = tile[1];
                    tile[1] = tile[0];
                    tile[0] = t;
                    return true;
                }
                else if (t->getNum() == tile[1]->getNum() + 1) {
                    tile[2] = t;
                    return true;
                }
                else {
                    return false;
                }
            }
            else if (tile[0]->getNum() + 2 == tile[1]->getNum() &&
                t->getNum() == tile[0]->getNum() + 1) {
                tile[2] = tile[1];
                tile[1] = t;
                return true;
            }
            else {
                return false;
            }
        }
    }

    void removeTile(Tile* t) {
        for (int i = 0; i < 3; i++) {
             if (t->getTileCode() == tile[i]->getTileCode()) {
                for (int j = i; j < 2; j++) {
                    tile[j] = tile[j + 1];
                    tile[2] = nullptr;
                }
            }
        }
    }
};

enum GroupType {
    SHUN, KE, GANG
};

///////////////
//Hand
///////////////

class Hand {
private:
    Tile* tile[14];

public:
    void sort() {
        std::sort(tile, tile+14, compareTile);
    }

    Tile* getTile(int index) {
        return tile[index];
    }

    int countXiangting() {
        std::vector<Group> groups;
        bool choose[14];
        for (int i = 0; i < 14; i++) {

            for (int j = i + 1; j < 14; j++) {
                for (int k = j + 1; k < 14; k++) {
                }
            }
        }
    }

    void checkChi() {

    }
};

///////////////
//Algorithm
///////////////
