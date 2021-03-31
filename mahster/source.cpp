#include <iostream>
#include "pymj.h"
#include "mahjong.h"

int main() {
    std::string s;
    std::cin >> s;
    
    
    Hand hand = parseHand(s);
    auto hands = hand.split();
    //for (auto h : hands) {
    //    std::cout << h << " " << h.groupXt() << '\n';
    //}
    std::cout << hands.back().groupXt() << "��" << '\n';
    auto analyze = cutAnalyze(s);
    for (auto it = analyze.begin(); it != analyze.end(); it++) {
        std::cout << it->first << " ";
        std::cout << it->second << '\n';
    }
    return 0;
}