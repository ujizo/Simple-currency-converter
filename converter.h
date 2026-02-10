#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <map>

class Converter {
private:
    Api api;
    std::map<std::string, double> cache;
    
    double fetchRate(const std::string& from, const std::string& to);
    
public:
    Converter();
    
    double convert(double amount, const std::string& from, const std::string& to);
    void clearCache();
};

#endif