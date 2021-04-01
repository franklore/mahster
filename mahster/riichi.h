#pragma once
#include <string>
#include "mahjong.h"

class Yaku {
public:
    virtual int getHan() = 0;

    virtual std::string getName() = 0;

    virtual bool check(const Hand& hand) = 0;
};

