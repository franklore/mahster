#pragma once

#include "mahjong.h"

std::map<std::string, std::string> cutAnalyze(std::string s) {
    Hand hand = parseHand(s);
    auto xt = hand.cutAnalyze();
    std::map<std::string, std::string> m;
    for (auto it = xt.begin(); it != xt.end(); ++it) {
        std::string tilename = it->first.toString();
        std::string liststr = show(it->second);
        m.insert(std::pair<std::string, std::string>(tilename, liststr));
    }
    return m;
}