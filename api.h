#ifndef API_H
#define API_H

#include <string>

class Api {
private:
    std::string base_url = "https://api.exchangerate-api.com/v4/latest/";

    std::string httpGet(const std::string& url);

public:
    double getRate(const std::string& from, const std::string& to);
};

#endif
