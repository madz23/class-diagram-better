#pragma once

#include "Transmission.hh"
#include "Catalytic_Converter.hh"
#include "Brake.hh"
#include "Wheel.hh"
#include "Muffler.hh"
#include <vector.h>

// CAR LAYOUT, uses push_back
//     FRONT
// ------------
// | 1      2 |
// |          |
// |          |
// | 3      4 |
// ------------
//      REAR

class Chassis{
    private:
        std::vector<Wheel> wheels;
        std::vector<Brake> brakes;
        Catalytic_Converter cat;
        Transmission trans;
        Muffler muff;
        
    public:

        Chassis();
        Chassis(std::vector<Wheel> w, std::vector<Brake> b, Catalytic_Converter c, Transmission t, Muffler m);

        // Setters
        // Initially sets to 1 type of wheel, can be changed later
        void setWheels(Wheel w, int amt){
            for(int i = 0; i < amt; i++){
                wheels.push_back(w);
            }
        }
        // Initially sets to 1 type of brake, can be changed later. Wheel has to be set first
        void setBrakes(Brake b){
            for(auto &w : wheels){
                brakes.push_back(b);
            }
        }
        void setCat(Catalytic_Converter c){ cat = c; }
        void setTrans(Transmission t){ trans = t; }
        void setMuffler(Muffler m){ muff = m; }

        // Getters
        std::vector<Wheel> getWheels() const { return wheels; }
        std::vector<Brake> getBrakes() const { return brakes; }
        Catalytic_Converter getCat() const { return cat; }
        Transmission getTrans() const { return trans; }
        Muffler getMuffler() const { return muff; }

        
};