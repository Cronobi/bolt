#pragma once
#include <string>
#include <vector>
using namespace std;

struct SearchResult {
    string name;
    string description;
    string url;
    string clone_URL;
};

class Search{
    public:
    vector<SearchResult> search(string package_name);
};