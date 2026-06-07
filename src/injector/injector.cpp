#include "injector.hpp"
#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
using namespace std;

namespace fs = filesystem;

void Injector::inject(string package_name)
{
  bool is_cmake = fs::exists("CMakeLists.txt");
  bool is_meson = fs::exists("meson.build");

  if (is_cmake)
  {
    ofstream file("CMakeLists.txt", ios::app);
    file << "add_subdirectory(bolt_packages/" + package_name + ")" << endl;
    file << "target_link_libraries(${PROJECT_NAME} " + package_name + ")" << endl;
    file.close();

    cout << "Success" << endl;
  }
  else if (is_meson)
  {
    ofstream file("meson.build", ios::app);
    file << "subproject('" + package_name + "')" << endl;
    file.close();

    cout << "Success" << endl;
  }
  else
  {
    cout << "Error: No build file found!" << endl;
    cout << "Make sure you are inside a C++ project" << endl;
  }
}
void Injector::remove(string package_name)
{
  bool is_cmake = fs::exists("CMakeLists.txt");
  bool is_meson = fs::exists("meson.build");

  if (is_cmake)
  {
    ifstream infile("CMakeLists.txt");
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
    ofstream outfile("CMakeLists.txt");
    for (string &l : lines)
    {
      outfile << l << endl;
    }
    outfile.close();
    cout << package_name << " removed from CMakeLists.txt!" << endl;
  }
  else if (is_meson)
  {
    ifstream infile("meson.build");
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
    ofstream outfile("meson.build");
    for (string &l : lines)
    {
      outfile << l << endl;
    }
    outfile.close();
    cout << package_name << " removed from meson.build!" << endl;
  } else {
    cout << "Error: no build file found!" << endl;
  }
}
