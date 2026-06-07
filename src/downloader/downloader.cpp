#include "downloader.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;

namespace fs = filesystem;
string current_dir = fs::current_path().string();

void Downloader::download(string package_name, string clone_url) {
  string target = current_dir + "/bolt/packages/" + package_name;

  if (fs::exists(target))
  {
    cout << package_name << " Already exists, skipping..." << endl;
    return;
  }
  
  string command = "git clone " + clone_url + " " + current_dir +
                   "/bolt_packages/" + package_name;

  system(command.c_str());
}

void Downloader::remove(string package_name) {
  string target = current_dir + "/bolt_packages/" + package_name;

  if (fs::exists(target))
  {
    fs::remove_all(target);
    cout << package_name << " removed successfully..." << endl;
  }else {
    cout << package_name << " Not found!..." << endl;
  }
  
}
