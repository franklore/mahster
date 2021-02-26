#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <type_traits>
////////////////
// Tile
////////////////
 
enum class TileCode {
    TILE_1M, TILE_2M, TILE_3M, TILE_4M, TILE_5M, TILE_6M, TILE_7M, TILE_8M, TILE_9M,
    TILE_1P, TILE_2P, TILE_3P, TILE_4P, TILE_5P, TILE_6P, TILE_7P, TILE_8P, TILE_9P,
    TILE_1S, TILE_2S, TILE_3S, TILE_4S, TILE_5S, TILE_6S, TILE_7S, TILE_8S, TILE_9S,
    TILE_DONG, TILE_NAN, TILE_XI, TILE_BEI, TILE_ZHONG, TILE_FA, TILE_BAI,
    TILE_EMPTY,
};

enum class TileSuit {
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
    Tile() : tileCode(TileCode::TILE_EMPTY) {

    }

    Tile(TileCode code) : tileCode(code) {

    }

    Tile(const Tile& t) : tileCode(t.getTileCode()) {

    }

    inline int getNum() const {
        return getSuit() == TileSuit::ZI ? 0 : (int)tileCode % 9 + 1;
    }

    inline TileSuit getSuit() const {
        return (TileSuit)((int)tileCode / 9);
    }

    inline TileCode getTileCode() const {
        return tileCode;
    }

    int operator- (const Tile& a) const {
        if (getSuit() != a.getSuit()) {
            return 9;
        }
        else {
            return getNum() - a.getNum();
        }
    }

    Tile operator+ (int i) const {
        if (getSuit() == TileSuit::ZI || getNum() == 9) {
            return Tile(TileCode::TILE_EMPTY);
        }
        else {
            return Tile(TileCode((int)getTileCode() + 1));
        }
    }

    Tile operator- (int i) const {
        if (getSuit() == TileSuit::ZI || getNum() == 1) {
            return Tile(TileCode::TILE_EMPTY);
        }
        else {
            return Tile(TileCode((int)getTileCode() + 1));
        }
    }

    bool operator== (const Tile& a) const {
        return getTileCode() == a.getTileCode();
    }

    bool operator!= (const Tile& a) const {
        return getTileCode() != a.getTileCode();
    }

    bool operator== (TileCode code) const {
        return getTileCode() == code;
    }

    bool operator != (TileCode code) const {
        return getTileCode() != code;
    }

    bool operator> (const Tile& a) const {
        return a.getTileCode() > a.getTileCode();
    }

    bool operator< (const Tile& a) const {
        return a.getTileCode() < a.getTileCode();
    }
};


///////////////
//Group
///////////////
enum class GroupType {
    SHUN, KE, GANG, PAIR, SINGLE, EMPTY
};


class Group {
private:
    Tile tiles[3];

    GroupType type = GroupType::EMPTY;

public:
    inline int count() const {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            if (tiles[0] != TileCode::TILE_EMPTY) {
                count++;
            }
        }
        return count;
    }

    void sort() {
        Tile temp;
        if (tiles[0] > tiles[1]) {
            temp = tiles[0];
            tiles[0] = tiles[1];
            tiles[1] = temp;
        }
        if (tiles[1] > tiles[2]) {
            temp = tiles[1];
            tiles[1] = tiles[2];
            tiles[2] = temp;
        }
        if (tiles[0] > tiles[1]) {
            temp = tiles[0];
            tiles[0] = tiles[1];
            tiles[1] = temp;
        }
    }

    bool add(Tile& t) {
        tiles[count()] = t;
        sort();
    }

    bool tryAdd(Tile& t) {
        if (count() == 0) {
            add(t);
            type = GroupType::SINGLE;
            return true;

        }
        else if (count() == 1) {
            if (t == tiles[0]) {
                add(t);
                type = GroupType::PAIR;
                return true;
            }
            else if (abs(t - tiles[0]) <= 2) {
                add(t);
                type = GroupType::SHUN;
                return true;
            }
            else {
                return false;
            }
        }
        else if (count() == 2) {
            if (type == GroupType::PAIR && t == tiles[1]) {
                add(t);
                type = GroupType::KE;
                return true;
            }
            else if (type == GroupType::SHUN && tiles[1] - tiles[0] == 1 && (t == tiles[0] - 1 || t == tiles[1] + 1)) {
                add(t);
                type = GroupType::SHUN;
                return true;
            }
            else if (type == GroupType::SHUN && tiles[1] - tiles[0] == 2 && t == tiles[0] + 1) {
                add(t);
                type = GroupType::SHUN;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    void remove(Tile& t) {
        for (int i = 2; i >= 0; i--) {
            if (tiles[i] == t) {
                tiles[i] = TileCode::TILE_EMPTY;
            }
        }
        sort();
    }


};

///////////////
//Hand
///////////////

class Hand {
private:
    Tile tiles[14];

public:
    Hand(Tile* input_tiles) {
        for (int i = 0; i < 14; i++) {
            tiles[i] = input_tiles[i];
        }
    }
    
    void sort() {
        std::sort(tiles, tiles+14);
    }

    Tile getTile(int index) {
        return tiles[index];
    }

    int countXiangting() {
        std::vector<Group> groups;
        for (int i = 0; i < 14; i++) {
            for (auto it = groups.begin(); it != groups.end(); it++) {
                if (!it->tryAdd(tiles[i])) {
                    Group group;
                    group.tryAdd(tiles[i]);
                    groups.push_back(group);
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
