#include "manifest.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

namespace fs = filesystem;

void Manifest::addDependency(string package_name, string clone_url)
{
    bool is_toml = fs::exists("bolt.toml");
    ofstream file("bolt.toml", ios::app);

    if (!is_toml)
    {
        file << "[dependencies]" << endl;
    }
    file << package_name + " = \"" + clone_url + "\"" << endl;
    file.close();
    cout << "Your package is saved!";
}

vector<pair<string, string>> Manifest::getDependencies()
{
    vector<pair<string, string>> deps;
    ifstream file("bolt.toml");
    string line;
    while (getline(file, line))
    {
        if (line == "[dependencies]")
        {
            continue;
        }
        int pos = line.find(" = ");
        string name = line.substr(0, pos);
        string url = line.substr(pos + 3);
        url = url.substr(1, url.size() - 2);
        deps.push_back({name, url});
    }
    return deps;
}

void Manifest::removeDependency(string package_name)
{
    bool is_bolt = fs::exists("bolt.toml");

    if (is_bolt)
    {
        ifstream infile("bolt.toml");
        vector<string> lines;
        string line;
        while (getline(infile, line))
        {
            if (line.find(package_name) != string::npos)
            {
                continue;
            }
            lines.push_back(line);
        }
        infile.close();
        ofstream outfile("bolt.toml");
        for (string &l : lines)
        {
            outfile << l << endl;
        }
        outfile.close();
        cout << package_name << " removed from bolt.toml" << endl;
    } else {
        cout << "bolt.toml not found!" << endl;
        cout << "Run 'bolt add <package>' first" << endl;
    }
}
