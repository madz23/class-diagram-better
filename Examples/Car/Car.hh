#pragma once

#include "Vehicle.hh"

class Car : public Vehicle{
    private:
        int gasMileage;
    public:
        Car();
        Car(int gas, Vehicle v);

        // Setters
        void setGasMileage(int g){ gasMileage = g; }

        // Getters
        int getGasMileage() const { return gasMileage; }
};
