#include <string>
#include <iostream>
#include <random>
#include "horse.hh"

// author: Madison May
// An example class for experimenting with the UI

using std::string;

class MiniHorse: public Horse {
    public: 
        bool flight;
        MiniHorse(string n) {
            name = n;
            size = "small";
        }
};