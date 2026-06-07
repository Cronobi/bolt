#include<iostream>
#include <ostream>
#include "cli/cli.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Bolt - C++ Package Manager" << endl;
        cout << "Usage: " << endl;
        cout << " bolt add <package> " << endl;
        cout << " bolt remove <package> " << endl;
        cout << " bolt search <package> " << endl;
        cout << " bolt install " << endl;
        cout << " bolt update " << endl;
        return 1;
    }

    CLI cli;
    cli.parse(argc, argv);
    return 0;
}