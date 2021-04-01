#pragma once

#include "mahjong.h"

std::map<std::string, std::vector<std::string>> cutAnalyze(std::string s) {
    Hand hand = parseHand(s);
    auto xt = hand.cutAnalyze();
    std::map<std::string, std::vector<std::string>> m;
    for (auto it = xt.begin(); it != xt.end(); ++it) {
        std::string tilename = it->first.toString();
        std::vector<std::string> liststr(it->second.begin(), it->second.end());
        m.insert(std::pair<std::string, std::vector<std::string>>(tilename, liststr));
    }
    return m;
}
