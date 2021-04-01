%module pymj_core

%include "std_map.i"
%include "std_string.i"
%include "std_vector.i"

namespace std{
    %template(stringVector) vector<string>;
    %template(cutmap) map<string, vector<string>>;
}

%{
#include "../mahster/pymj.h"
%}

std::map<std::string, std::vector<std::string>> cutAnalyze(std::string s);
