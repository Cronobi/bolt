#pragma once
#include <string>
using namespace std;

class Downloader {
    public:
    void download(string package_name, string clone_url);
    void remove(string package_name);
};