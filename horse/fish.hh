#include <string>
#include <iostream>
#include <random>
#include "animal.hh"

// author: Madison May
// An example class for experimenting with the project

using std::string;

class Fish: public Animal{
    public: 
        bool saltWater;
        float length;
        string favoriteFood;

        Fish() {};
};
