# pragma once

#include "EngineBay/EngineBay.hh"
#include "Chassis/Chassis.hh"

class Vehicle{
    private:
        int year;
        float mileage; // For cars which might have a decimal value mileage
        float value; // For cents if necessary
        std::string manufacturer;
        std::string model;
        EngineBay engineBay;
        Chassis chassis;
    public:
        Vehicle();
        Vehicle(EngineBay e, Chassis c, int y, float m, float v, std::string man, std::string mod);

        // Setters
        void setYear(int y){ year = y; }
        void setMileage(float mile){ mileage = mile; }
        void setValue(float val){ value = val; }
        void setManufacturer(std::string man){ manufacturer = man; }
        void setModel(std::string mod){ model = mod; }
        void setEngineBay(EngineBay e){ engineBay = e; }
        void setChassis(Chassis c){ chassis = c; }

        // Getters
        int getYear() const { return year; }
        float getMileage() const { return mileage; }
        float getValue() const { return value; }
        std::string getManufacturer() const { return manufacturer; }
        std::string getModel() const { return model; }
        EngineBay getEngineBay() const { return engineBay; }
        Chassis getChassis() const { return chassis; } 


};