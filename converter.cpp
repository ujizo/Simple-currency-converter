#include "converter.h"
#include <iostream>
#include <chrono>

Converter::Converter() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

double Converter::fetchRate(const std::string& from, const std::string& to) {
    double rate = api.getRate(from, to);
    
    if (rate > 0) {
        std::string key = from + "_" + to;
        cache[key] = rate;
    }
    
    return rate;
}

double Converter::convert(double amount, const std::string& from, const std::string& to) {
    if (from == to) return amount;
    
    std::string key = from + "_" + to;
    
    if (cache.find(key) != cache.end()) {
        return amount * cache[key];
    }
    
    double rate = fetchRate(from, to);
    
    if (rate < 0) {
        std::cerr << "Error: Could not get exchange rate" << std::endl;
        return -1;
    }
    
    return amount * rate;
}

void Converter::clearCache() {
    cache.clear();
}