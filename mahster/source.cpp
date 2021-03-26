#include <iostream>
#include "mahjong.h"

int main() {
    std::string s;
    std::cin >> s;
    
    
    Hand hand = parseHand(s);
    auto hands = hand.split();
    //for (auto h : hands) {
    //    std::cout << h << " " << h.groupXt() << '\n';
    //}
    std::cout << hands.back().groupXt() << "Ïò" << '\n';
    auto analyze = hand.cutAnalyze();
    for (auto it = analyze.begin(); it != analyze.end(); it++) {
        std::cout << it->first << " ";
        std::cout << show(it->second) << '\n';
    }
    return 0;
}