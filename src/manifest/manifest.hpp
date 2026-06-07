#pragma once
#include <vector>
#include <string>

using namespace std;

class Manifest
{
    public:
    void addDependency(string package_name, string clone_url);
    vector<pair<string,string>> getDependencies();
    void removeDependency(string package_name);
};
