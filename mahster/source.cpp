#include <iostream>
#include "mahjong.h"

int main() {
    Hand hand = parseHand("112233s");
    auto hands = hand.split(false);
    for (auto h : hands) {
        std::cout << h << '\n';
    }
    return 0;
}