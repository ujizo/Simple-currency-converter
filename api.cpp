#include "api.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

static size_t writeCallback(void* data, size_t size, size_t nmemb, std::string* output) {
    size_t total = size * nmemb;
    output->append((char*)data, total);
    return total;
}

std::string Api::httpGet(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
        }
        
        curl_easy_cleanup(curl);
    }
    
    return response;
}

double Api::getRate(const std::string& from, const std::string& to) {
    std::string url = base_url + from;
    std::string response = httpGet(url);
    
    try {
        json data = json::parse(response);
        return data["rates"][to];
    } catch (...) {
        return -1;
    }
}
