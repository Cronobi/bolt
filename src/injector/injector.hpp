#pragma once
#include <string>
using namespace std;
class Injector {
public:
  void inject(string package_name);
  void remove(string package_name);
};
