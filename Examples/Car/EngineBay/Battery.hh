#pragma once

class Battery{
    private:
        double CA;
        double CCA;
        double RC;
        std::string batteryType;
        const bool isInOcean = false; // Inspired after car battery in ocean meme (cannot change because dont do that)
    
    public:
        Battery();
        Battery(double crank, double coldCrank, double reserveCap, std::string type);

        // Setters
        void setCrankAmps(int amps){ CA = amps; }
        void setColdCrankAmps(int amps){ CCA = amps; }
        void setReserveCapacity(int minutes){ RC = minutes; }
        void setBatteryType(std::string type){ batteryType = type; }

        // Getters
        double getCrankAmps() const { return CA; }
        double getColdCrankAmps() const { return CCA; }
        double getReserveCapacity() const { return RC; }
        std::string getBatteryType() const { return baffleType; }
};