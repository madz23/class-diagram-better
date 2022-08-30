#include <string>
#include <iostream>
#include <random>
#include "horse.hh"

// author: Madison May
// An example class for experimenting with the UI

using std::string;

class Pegasus: public Horse {
    public: 
        bool flight;
        Pegasus(string n) {
            name = n;
            flight = true;
        }
};