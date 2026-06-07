#include"search.hpp"
#include <cstddef>
#include<curl/curl.h>
#include <curl/easy.h>
#include <exception>
#include<nlohmann/json.hpp>
#include<iostream>
#include <string>
#include <vector>

using namespace std;
using json = nlohmann::json;

size_t writeCallback(char* data, size_t size, size_t nmemb, string* output) {
    output->append(data, size * nmemb);
    return size * nmemb;
}

vector<SearchResult> Search::search(string package_name) {
    vector<SearchResult> results;

    string url = "https://api.github.com/search/repositories?q=" + package_name + "+language:cpp";

    cout << "Searching: " << url << endl;

    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "bolt-package-manager");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    } else {
        cout<< "Curl failed to initialize!" << endl;
    }

    cout << "Response length: " << response.size() << endl;
    cout << "Response: " << response.substr(0, 200) << endl;

    try {
    json data = json::parse(response);
    for (auto& item : data["items"]) {
        SearchResult result;
        result.name = item["name"];
        result.description = item.value("description", "No description");
        result.url = item["html_url"];
        result.clone_URL = item["clone_url"];
        results.push_back(result);    
        }
    } catch (exception& e) {
        cout << "Error parsing response: " << e.what() <<endl;
    }

    return  results;
}