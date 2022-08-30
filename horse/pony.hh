#include <string>
#include <iostream>
#include <random>
#include "horse.hh"

// author: Madison May
// An example class for experimenting with the UI

using std::string;

class Pony: public Horse {
    public: 
        Pony(string n) {
            name = n;
            height = 14;
        }
};