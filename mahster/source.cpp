#include <iostream>
#include "pymj.h"
#include "mahjong.h"

int main() {
    //std::string s;
    //std::cin >> s;
    Hand hand(randomTile(14));
    hand.sort();
    clock_t begin, end;
    std::cout << hand << std::endl;
    begin = clock();
    auto cut = hand.cutAnalyze();
    end = clock();
    for (auto it = cut.begin(); it != cut.end(); it++) {
        std::cout << it->first << " ";
        std::cout << it->second << std::endl;
    }
    std::cout << "in " << end - begin << "ms" << std::endl;

    return 0;
}