#pragma once

class Transmission{
    private:
        int planetTeeth;
        int sunTeeth; // Assumes 3 planets and 1 sun with auto-calculated clutchPlate diameter
        int clutchPlateAmt;
        int clutchDiskAmt;
        bool isAutomatic;
        double oilPumpLevel;
        bool isCVT;
        double vacuumModulatorPressure;

    public:
        Transmission();
        Transmission(int pT, int sT, int cPA, int cDA, bool iA, bool lC, double oil, bool iC, double vMP);

        // Setters
        void setPlanetTeeth(int amt){ planetTeeth = amt;}
        void setSunTeeth(int amt){ sunTeeth =  amt; }
        void setGearAmt(int amt){ 
            clutchDiskAmt = amt;
            clutchPlateAmt = amt;
        }
        void setAutomatic(bool isA){
            if(isA == false){
                // Cannot have CVT manual
                isAutomatic = false;
                isCVT = false;
            }
            else{
                isAutomatic = true;
            }    
        }
        void setCVT(bool isC){
            if(isAutomatic == true){
                isCVT = isC;
            }
            else{
                isCVT = false;
            }
        }
        void setOilPumpLevel(double l){ oilPumpLevel = l; }
        void setVacuum(double p){ vacuumModulatorPressure = p; }

        // Getters
        int getPlanetTeeth() const { return planetTeeth; }
        int getSunTeeth() const { return sunTeeth; }
        int getGearAmt() const { return clutchDiskAmt; }
        bool isAuto() const { return isAutomatic; }
        bool hasCVT() const { return isCVT; }
        double getOilPumpLevel() const { return oilPumpLevel; }
        double getVacuum() const { return vacuumModulatorPressure; }       
};