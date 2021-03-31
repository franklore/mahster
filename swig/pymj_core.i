%module pymj_core

%include "std_map.i"
%include "std_string.i"

namespace std{
    %template(map_string_string) map<string, string>;
}

%{
#include "../mahster/pymj.h"
%}

std::map<std::string, std::string> cutAnalyze(std::string s);