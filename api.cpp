#include "api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

double Api::getRate(const std::string& from, const std::string& to) {
    if (from == to) return 1.0;

    CURL* curl = curl_easy_init();
    std::string response;

    if(curl) {
        std::string url = "https://cdn.moneyconvert.net/api/latest.json";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            return 0.0;
        }
    }

    try {
        auto json = nlohmann::json::parse(response);


        if (!json["rates"].contains(from) || !json["rates"].contains(to)) {
            std::cerr << "Currency not found!" << std::endl;
            return 0.0;
        }


        double rateFrom = json["rates"][from];
        double rateTo = json["rates"][to];


        double result = rateTo / rateFrom;

        std::cout << "Debug: 1 " << from << " = " << result << " " << to << std::endl;

        return result;

    } catch(const std::exception& e) {
        std::cerr << "JSON error: " << e.what() << std::endl;
        return 0.0;
    }
}

std::string Api::fetchExchangeRates() {
    return getRate("USD", "RUB") > 0 ? "success" : "failed";
}

