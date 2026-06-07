/* ____   ____  _   _______
 |  _ \ / __ \| | |__   __|
 | |_) | |  | | |    | |
 |  _ <| |  | | |    | |
 | |_) | |__| | |____| |
 |____/ \____/|______|_|

*  Bolt - C++ Package Manager
*   Version: 1.0.0
*   Author: Cronobi
*   License: MIT
*/

#include "cli.hpp"
#include "../downloader/downloader.hpp"
#include "../search/search.hpp"
#include "../injector/injector.hpp"
#include "../manifest/manifest.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void CLI::parse(int argc, char *argv[])
{
  int index;
  string command = argv[1];
  if (command == "add")
  {
    if (argc < 3)
    {
      cout << "Usage: bolt add <package>" << endl;
      return;
    }
    string package = argv[2];
    Search searcher;
    vector<SearchResult> results = searcher.search(package);

    for (int i = 0; i < (int)results.size(); i++)
    {
      cout << i + 1 << ". " << results[i].name << endl;
      cout << " " << results[i].description << endl;
      cout << " " << results[i].url << endl;
      cout << endl;
    }

    cout << "Enter Your index of your library you want to add: " << endl;
    cin >> index;
    Downloader down;
    int picked = index - 1;
    down.download(results[picked].name, results[picked].clone_URL);

    Injector injector;
    injector.inject(results[picked].name);

    Manifest manifest;
    manifest.addDependency(results[picked].name, results[picked].clone_URL);
  }
  else if (command == "remove")
  {
    if (argc < 3)
    {
      cout << "Usage: bolt remove <package>" << endl;
      return;
    }
    string package = argv[2];
    Downloader down;
    down.remove(package);
    Injector injector;
    injector.remove(package);
    Manifest manifest;
    manifest.removeDependency(package);
  }
  else if (command == "search")
  {
    if (argc < 3)
    {
      cout << "Usage: bolt search <package>" << endl;
      return;
    }
    string package = argv[2];
    Search searcher;
    vector<SearchResult> results = searcher.search(package);

    for (int i; i < (int)results.size(); i++)
    {
      cout << i + 1 << ". " << results[i].name << endl;
      cout << " " << results[i].description << endl;
      cout << " " << results[i].url << endl;
      cout << endl;
    }
  }
  else if (command == "install")
  {
    Manifest manifest;
    vector<pair<string, string>> deps = manifest.getDependencies();

    for (auto &dep : deps)
    {
      Downloader down;
      down.download(dep.first, dep.second);
      Injector injector;
      injector.inject(dep.first);
    }

    cout << "All dependencies installed!" << endl;
  }
  else if (command == "-h" || command == "-help")
  {
    cout << "Bolt - C++ Package Manager" << endl;
    cout << "Usage: " << endl;
    cout << " bolt add <package> " << endl;
    cout << " bolt remove <package> " << endl;
    cout << " bolt search <package> " << endl;
    cout << " bolt install " << endl;
  }
  else
  {
    cout << "Unknown command: " << command << endl;
    cout << "Run 'bolt -h' for help." << endl;
  }
}
