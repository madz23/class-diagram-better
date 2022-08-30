#include <string>
#include <iostream>
#include <random>
#include "horse.hh"

// author: Madison May
// An example class for experimenting with the UI

using std::string;

class Unicorn: public Horse {
    public: 
        bool magic;
        Unicorn(string n) {
            name = n;
            magic = true;
        }
};