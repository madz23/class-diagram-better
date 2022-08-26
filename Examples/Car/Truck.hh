#pragma once

#include "Vehicle.hh"

class Truck : public Vehicle{
  private:
    bool awd; // Assuming is otherwise awd or not
    int towingCapacity;

  public:
    Truck();
    Truck(bool a, int tC, Vehicle v);

    // Setters
    void setAwd(bool isAWD){ awd = isAWD; }
    void setTowing_capacity(int towing){ towingCapacity = towing; }

    // Getters
    bool getAwd() const{ return awd; }
    int getTowing_capacity() const{ return towingCapacity; }
};
