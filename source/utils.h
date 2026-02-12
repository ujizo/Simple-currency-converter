#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace utils {
    bool isValidCurrency(const std::string& code);
    std::string formatMoney(double amount, const std::string& currency);
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string trim(const std::string& str);
    std::string toUpper(const std::string& str);
}

#endif 
