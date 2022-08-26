#pragma once

class Radiator{
    private:
        double fluidLevel;
        double fluidTemp;
        bool isCellular;
        int amtFins;

    public:
        Radiator();
        Radiator(double level, double temp, bool cell, int fins);

        // Setters
        void setFluidLevel(double l){ fluidLevel = l; }
        void setFluidTemp(double T){ fluidTemp = T; }
        void setCellular(bool isC){ isCellular = isC; }
        void setAmtFins(int amt){ amtFins = amt; }

        // Getters
        double getFluidLevel() const { return fluidLevel; }
        double getFluidTemp() const { return fluidTemp; }
        bool getCellular() const { return isCellular; }
        int amtFins() const { return amtFins; }

};