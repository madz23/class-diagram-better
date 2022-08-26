#pragma once

#include "Air_Filter.hh"
#include "Alternator.hh"
#include "Battery.hh"
#include "Distributor.hh"
#include "Engine.hh"
#include "Oil_Filter.hh"
#include "Radiator.hh"

class EngineBay{
    private:
        Air_Filter air;
        Alternator alt;
        Oil_Filter oil;
        Battery batt;
        Distributor dist;
        Engine engine;
        Radiator rad;
    public:
        EngineBay();
        EngineBay(Air_Filter a, Alternator al, Oil_Filter o, Battery b, Distributor d, Engine e, Radiator r);

        // Setters
        void setAirFilter(Air_Filter a){ air = a; }
        void setAlternator(Alternator al){ alt = al; }
        void setOilFilter(Oil_Filter o){ oil = o; }
        void setBattery(Battery b){ batt = b; }
        void setDistributor(Distributor d){ dist = d; }
        void setEngine(Engine e){ engine = e; }
        void setRadiator(Radiator r){ rad = r; }

        // Getters
        Air_Filter getAirFilter() const { return air; }
        Air_Filter getAlternator() const { return alt; }
        Oil_Filter getOilFilter() const { return oil; }
        Battery getBattery() const { return batt; }
        Radiator getRadiator() const { return rad; }
        Distributor getDistributor() const { return dist; }

};