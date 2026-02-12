#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <map>
#include "api.h"

class Converter {
private:
    Api api;
    std::map<std::string, double> cache;

public:
    Converter();
    ~Converter();
    double convert(double amount, const std::string& from, const std::string& to);
    double fetchRate(const std::string& from, const std::string& to);
    void clearCache();
};

#endif
