#pragma once

class Alternator{
    private:
        const double torque_constant=746;
        bool isSalient;
        double outputCurrent;
        double efficiency;
        double altTemp;
        double torque;

    public:
        Alternator();
        Alternator(bool isS, double oC, double e, double T, double t);

        // Setters
        void setOutputCurrent(double c){
            outputCurrent = c;
        }
        void setIsSalient(bool sal){ isSalient = sal; }
        void setEfficiency(double e){ efficiency = e; }
        void setAltTemp(double T){ altTemp = T; }
        void setTorque(double t){ torque = t; }

        // Calculations to test other things beyong getters and setters
        void calculateOutputCurrent(){
            outputCurrent = (torque*efficiency)/torque_constant;
            if(altTemp > 120){
                outputCurrent *= 0.06042*alt_Temp;
            }
        }

        // Getters
        bool getSalient() const { return isSalient; }
        double getCurrent() const { return outputCurrent; }
        double getEfficiency() const { return efficiency; }
        double getTemp() const { return altTemp; }
        double getTorque() const { return torque; }

}