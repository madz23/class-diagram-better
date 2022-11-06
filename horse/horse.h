#include <string>
#include <iostream>
#include <random>
#include "animal.hh"

// author: Madison May
// An example class for experimenting with the project

using std::string;

class Horse: public Animal{
    public: 
        int height;
        int speed;
        int MIN = 40;
        int MAX = 65;

        // constructors
        Horse() {
            age = 0;
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(MIN, MAX);
        }
        Horse(string n) {
            name = n;
            age = 0;
            std::random_device rd;
            std::default_random_engine eng(rd());
            std::uniform_int_distribution<int> distr(MIN, MAX);
        }

        // methods
        int run(int minutes) {
            int speedInMS = speed * 1000 / 60;
            return speedInMS * minutes;
        }
        
};
