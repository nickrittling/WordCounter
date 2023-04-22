#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include "CLI11.hpp"
#include "bloom.h"
std::string StringInput(const std::string& input) {
    std::string result;
    std::remove_copy_if(input.begin(), input.end(), std::back_inserter(result),
        [](char c) { return !std::isalnum(c); });
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return result;
}//end StringInput



