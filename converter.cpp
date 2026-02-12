#include "converter.h"
#include <curl/curl.h>
#include <iostream>

Converter::Converter() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Converter::~Converter() {
    curl_global_cleanup();
}

double Converter::fetchRate(const std::string& from, const std::string& to) {
    std::string key = from + "_" + to;

    // Проверяем кэш
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }


    double rate = api.getRate(from, to);
    if (rate > 0) {
        cache[key] = rate;
    }

    return rate;
}

double Converter::convert(double amount, const std::string& from, const std::string& to) {
    if (from == to) return amount;

    double rate = fetchRate(from, to);
    return amount * rate;
}

void Converter::clearCache() {
    cache.clear();
}
