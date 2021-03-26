#pragma once
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <type_traits>
#include <iostream>
#include <exception>
#include <time.h>
#include <unordered_map>

////////////////
//Math
///////////////
inline int min(int a, int b) {
    return a < b ? a : b;
}

inline int max(int a, int b) {
    return a > b ? a : b;
}


////////////////
// Tile
////////////////

class Tile {
public:
    enum class TileSuit {
        WAN, TONG, SUO, ZI, INVALID
    };

private:
    int num;

    TileSuit suit;

public:
    Tile() {
        this->num = 0;
        this->suit = TileSuit::INVALID;
    }

    Tile(int num, TileSuit suit) {
        this->num = num;
        this->suit = suit;
    }

    Tile(int num, char suit) {
        this->num = num;
        switch (suit) {
        case 'm': this->suit = TileSuit::WAN; break;
        case 'p': this->suit = TileSuit::TONG; break;
        case 's': this->suit = TileSuit::SUO; break;
        case 'z': this->suit = TileSuit::ZI; break;
        default: this->suit = TileSuit::INVALID; break;
        }
    }

    Tile(const Tile& t) : num(t.getNum()), suit(t.getSuit()) {

    }

    inline int getNum() const {
        return num;
    }

    inline char getNumChar() const {
        return getNum() + '0';
    }

    inline TileSuit getSuit() const {
        return suit;
    }

    inline char getSuitChar() const {
        if (this->getSuit() == TileSuit::WAN) {
            return 'm';
        }
        else if (this->getSuit() == TileSuit::SUO) {
            return 's';
        }
        else if (this->getSuit() == TileSuit::TONG) {
            return 'p';
        }
        else if (this->getSuit() == TileSuit::ZI) {
            return 'z';
        }
        else {
            return '-';
        }
    }

    inline int getCode() const {
        return getNum() + (int)getSuit() * 9 - 1;
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
            return Tile();
        }
        else {
            return Tile(this->getNum() + i, this->getSuit());
        }
    }

    Tile operator- (int i) const {
        if (getSuit() == TileSuit::ZI || getNum() == 1) {
            return Tile();
        }
        else {
            return Tile(this->getNum() - i, this->getSuit());
        }
    }

    operator bool() const {
        return getSuit() != TileSuit::INVALID && getNum() >= 0 && getNum() <= 9;
    }

    bool operator== (const Tile& a) const {
        return getNum() == a.getNum() && getSuit() == a.getSuit();
    }

    bool operator!= (const Tile& a) const {
        return !operator==(a);
    }

    bool operator> (const Tile& a) const {
        return (int)getSuit() * 10 + getNum() > (int)a.getSuit() * 10 + a.getNum();
    }

    bool operator< (const Tile& a) const {
        return !operator==(a) && !operator>(a);
    }

    int distance(const Tile& a) const {
        return abs(operator-(a));
    }

    std::string toString() const {
        if (this->getSuit() == TileSuit::INVALID) {
            return "";
        }
        std::string str("00");
        str[0] = '0' + this->getNum();
        str[1] = getSuitChar();
        return str;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Tile& tile);
};

std::ostream& operator<< (std::ostream& stream, const Tile& tile) {

    stream << tile.toString();
    return stream;
}

namespace std {
    template<> struct hash<Tile> {
        std::size_t operator()(const Tile& t) const noexcept {
            return (size_t)t.getCode();
        }
    };
}

///////////////
//Group
///////////////
enum class GroupType {
    SHUN, KE, GANG, PAIR, DA, SINGLE, EMPTY
};


class Group {
private:
    Tile tiles[3];

    GroupType type = GroupType::EMPTY;

public:
    Group() {
        tiles[0] = Tile();
        tiles[1] = Tile();
        tiles[2] = Tile();
    }

    Group(const Tile& t1) {
        tiles[0] = t1;
        tiles[1] = Tile();
        tiles[2] = Tile();
        setType();
    }

    Group(const Tile& t1, const Tile& t2) {
        tiles[0] = t1;
        tiles[1] = t2;
        tiles[2] = Tile();
        setType();
    }

    Group(const Tile& t1, const Tile& t2, const Tile& t3) {
        tiles[0] = t1;
        tiles[1] = t2;
        tiles[2] = t3;
        setType();
    }

    Group(const Group& group) : type(group.type) {
        for (int i = 0; i < 3; i++) {
            tiles[i] = group.tiles[i];
        }
    }

    inline GroupType getType() {
        return type;
    }

    inline bool isComplete() {
        return type == GroupType::KE || type == GroupType::SHUN || type == GroupType::GANG;
    }

    inline int count() const {
        int count = 0;
        for (int i = 0; i < 3; i++) {
            if (tiles[i]) {
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

    void add(Tile& t) {
        tiles[count()] = t;
        setType();
    }

    bool checkCombine(Group& other) {
        if (count() + other.count() > 3) {
            return false;
        }
        Group g(*this);
        for (int i = 0; i < other.count(); i++) {
            g.add(other[i]);
        }
        g.setType();
        return g.type != GroupType::EMPTY;
    }
     
    bool contain(const Tile& t) {
        for (int i = 0; i < 3; i++) {
            if (tiles[i] == t) {
                return true;
            }
        }
        return false;
    }

    void remove(const Tile& t) {
        for (int i = 2; i >= 0; i--) {
            if (tiles[i] == t) {
                tiles[i] = Tile();
            }
        }
        sort();
    }

    std::string toString() const {
        if (count() == 0) {
            return "";
        }
        std::vector<char> str;
        str.push_back(tiles[0].getNumChar());
        for (int i = 1; i < count(); i++) {
            if (tiles[i].getSuit() != tiles[i - 1].getSuit()) {
                str.push_back(tiles[i].getSuitChar());
            }
            str.push_back(tiles[i].getNumChar());
        }
        str.push_back(tiles[count() - 1].getSuitChar());
        return std::string(str.begin(), str.end());
    }

    friend std::ostream& operator<< (std::ostream& stream, const Group& group);

    Tile& operator[] (int index) {
        return tiles[index];
    }

    const Tile& operator[] (int index) const {
        return tiles[index];
    }

 private:
    void setType() {
        sort();
        if (count() == 0) {
            type = GroupType::EMPTY;
        }
        else if (count() == 1) {
            type = GroupType::SINGLE;
        }
        else if (count() == 2) {
            if (tiles[1] == tiles[0]) {
                type = GroupType::PAIR;
            }
            else if (tiles[1].distance(tiles[0]) <= 2) {
                type = GroupType::DA;
            }
            else {
                type = GroupType::EMPTY;
            }
        }
        else if (count() == 3) {
            if (tiles[1] == tiles[0] && tiles[2] == tiles[1]) {
                type = GroupType::KE;
            }
            else if (tiles[2] - tiles[1] == 1 && tiles[1] - tiles[0] == 1) {
                type = GroupType::SHUN;
            }
            else {
                type = GroupType::EMPTY;
            }
        }
        else {
            type = GroupType::EMPTY;
        }
    }

};


std::ostream& operator<< (std::ostream& stream, const Group& group) {
        stream << group.toString();
        return stream;
}

bool checkGroup(const Tile& t1, const Tile& t2) {
    int dist = abs(t1 - t2);
    if (dist == 0) {
        return true;
    }
    else if (dist <= 2) {
        return true;
    }
    else {
        return false;
    }
}

bool checkGroup(const Tile& t1, const Tile& t2, const Tile& t3) {
    if (t1 == t2 && t2 == t3) {
        return true;
    }
    else {
        Tile tiles[3];
        tiles[0] = t1;
        tiles[1] = t2;
        tiles[2] = t3;
        std::sort(tiles, tiles + 3);
        if (tiles[1] - tiles[0] == 1 && tiles[2] - tiles[1] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
}

///////////////
//Hand
///////////////

class Hand {
private:
    std::vector<Group> groups;

    std::vector<Tile> tiles;

public:
    Hand(std::vector<Tile> tiles) : tiles(tiles) {
    }
    
    void sort() {
        std::sort(tiles.begin(), tiles.end());
    }

    Tile& operator[] (int index) {
        return tiles[index];
    }

    const Tile& operator[] (int index) const {
        return tiles[index];
    }

    int groupXt() {
        bool havePair = false;
        int xt = 8;
        int m = 0, d = 0, p = 0;
        for (auto it = groups.begin(); it != groups.end(); it++) {
            if (it->isComplete()) {
                m++;
            }
            else if (it->getType() == GroupType::PAIR) {
                p++;
            }
            else if (it->getType() == GroupType::DA) {
                d++;
            }
        }
        int v = p == 0 ? min(4 - m, d) : min(5 - m, d + p);
        return 8 - 2 * m - v;
    }

    std::unordered_map<Tile, std::vector<Tile>> cutAnalyze() {
        Hand base(*this);
        int currentXt = base.getXt();
        std::unordered_map<Tile, std::vector<Tile>> map;
        for (int i = 0; i < base.tiles.size(); i++) {
            Tile cut = base[i];
            if (map.find(cut) != map.end()) {
                continue;
            }
            std::vector<Tile> progress;
            for (int ti = 0; ti < 34; ti++) {
                int num = ti % 9 + 1;
                int suit = ti / 9;
                Tile t(num, (Tile::TileSuit)suit);
                base[i] = t;
                if (base.getXt() < currentXt) {
                    progress.push_back(t);
                }
            }
            if (!progress.empty()) {
                map.insert(std::pair<Tile, std::vector<Tile>> {cut, progress});
            }
            base[i] = cut;
        }
        return map;
    }

    int getXt() {
        std::vector<Hand> splits = split();
        return splits.back().groupXt();
    }

    std::vector<Hand> split() const {
        Hand copy(*this);
        copy.sort();
        std::vector<Hand> hands;
        std::vector<Hand> complete;
        hands.emplace_back(copy.tiles);
        
        int minXt = 8;
        int c = 0;
        while (!hands.empty()) {
            //std::cout << c++ << std::endl;
            //for (auto h : hands) {
            //    std::cout << h << '\n';
            //}
            //std::cout << "---" << std::endl;

            Hand base = hands.back();
            hands.pop_back();

            // if a hand's xiangting is no less than minXt, then pass
            int minProbablyXtOfBase = base.groupXt() - (base.tiles.size() / 3) * 2 - base.tiles.size() % 3 == 2 ? 1 : 0;
            if (minProbablyXtOfBase > minXt) {
                continue;
            }

            // if a hand contains 2 groups that can be combined together, then pass
            if (base.groups.size() >= 2) {
                bool canCombine = false;
                for (auto it = base.groups.begin(); it != base.groups.end() - 1; it++) {
                    if (base.groups.back().checkCombine(*it)) {
                        canCombine = true;
                        break;
                    }
                }
                if (canCombine) {
                    continue;
                }
            }

            if (base.tiles.empty()) {
                int baseXt = base.groupXt();
                if (baseXt > minXt) {
                    continue;
                }
                else if (baseXt == minXt) {
                    complete.push_back(base);
                    continue;
                }
                else {
                    minXt = baseXt;
                    complete.clear();
                    complete.push_back(base);
                    continue;
                }
                
            }

            Tile first = base[0];
            base.tiles.erase(base.tiles.begin());

            // always add SINGLE group
            Hand newhand(base);
            Group group(first);
            newhand.groups.push_back(group);
            hands.push_back(newhand);

            // find SHUN
            if (first.getSuit() == Tile::TileSuit::ZI) {
                continue;
            }

            bool have2 = false;
            for (size_t i = 0; i < base.tiles.size(); i++) {
                if (base[i] == first) {
                    continue;
                }
                if (base[i] - first == 1 && !have2) {
                    Hand newhand(base);
                    Group group(first, base[i]);
                    newhand.groups.push_back(group);
                    newhand.tiles.erase(newhand.tiles.begin() + i);
                    hands.push_back(newhand);
                    for (size_t j = 0; j < newhand.tiles.size(); j++) {
                        if (newhand.tiles[j] - first <= 1) {
                            continue;
                        }
                        if (newhand[j] - first == 2) {
                            Hand newhand3(newhand);
                            newhand3.groups.back().add(newhand.tiles[j]);
                            newhand3.tiles.erase(newhand3.tiles.begin() + j);
                            hands.push_back(newhand3);
                            break;
                        }
                    }
                    break;
                }
                if (base[i] - first == 2 && !have2) {
                    Hand newhand(base);
                    Group group(first, base[i]);
                    newhand.groups.push_back(group);
                    newhand.tiles.erase(newhand.tiles.begin() + i);
                    hands.push_back(newhand);
                }
                if (base[i] - first > 2) {
                    break;
                }
            }

            // find KE and PAIR
            if (base.tiles.size() >= 1 && base[0] == first) {
                Hand newhand(base);
                Group group(first, base[0]);
                newhand.groups.push_back(group);
                newhand.tiles.erase(newhand.tiles.begin());
                hands.push_back(newhand);
                if (base.tiles.size() >= 2 && base[1] == first) {
                    Hand newhand3(newhand);
                    newhand3.groups.back().add(newhand[0]);
                    newhand3.tiles.erase(newhand3.tiles.begin());
                    hands.push_back(newhand3);
                }
            }
        }
        return complete;
    }

    friend std::ostream& operator<< (std::ostream& stream, const Hand& hand);
};

std::ostream& operator<< (std::ostream& stream, const Hand& hand) {
    for (const Tile& t : hand.tiles) {
        stream << t;
    }
    stream << ' ';
    for (const Group& g : hand.groups) {
        stream << g << ' ';
    }
    return stream;
}

Hand parseHand(std::string str) {
    std::vector<Tile> tiles;
    int k = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == 'm' || str[i] == 's' || str[i] == 'p' || str[i] == 'z') {
            for (int j = k; j < i; j++) {
                int num = str[j] - '0';
                if (num >= 0 && num <= 9) {
                    tiles.push_back(Tile(str[j] - '0', str[i]));
                }
                else {
                    throw std::invalid_argument("invalid expression");
                }
            }
            k = i + 1;
        }
    }
    return Hand(tiles);
}

std::string show(std::vector<Tile> tiles) {
    std::vector<char> str;
    if (tiles.empty()) {
        return "";
    }
    else if (tiles.size() == 1) {
        return tiles[0].toString();
    }
    str.push_back(tiles[0].getNumChar());
    for (int i = 1; i < tiles.size(); i++) {
        if (tiles[i].getSuit() != tiles[i - 1].getSuit()) {
            str.push_back(tiles[i - 1].getSuitChar());
        }
        str.push_back(tiles[i].getNumChar());
    }
    str.push_back(tiles.back().getSuitChar());
    return std::string(str.begin(), str.end());
}

///////////////
//Algorithm
///////////////
