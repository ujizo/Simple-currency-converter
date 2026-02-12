#ifndef API_H
#define API_H

#include <string>

class Api {
public:
    double getRate(const std::string& from, const std::string& to);
    std::string fetchExchangeRates();
};

#endif
