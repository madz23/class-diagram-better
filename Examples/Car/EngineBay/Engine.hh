#pragma once

class Engine{
    private:
        double oxygenAmt;
        double sparkCurrent;
        int cylinderAmt;
        double oilAmt;
        double engineSize;

    public:
        Engine();
        Engine(double o, double c, int cA, double oA, double eS);

        // Setters
        void setOxygenAmt(double o){ oxygenAmt = o; }
        void setSparkCurrent(double c){ sparkCurrent = c; }
        void setCylinderAmt(int amt){ cylinderAmt = amt; }
        void setOilAmt(double amt){ oilAmt = amt; }
        void setEngineSize(double liter){ engineSize = liter; }

        // Getters
        double getOxygenAmt() const { return oxygenAmt; }
        double getSparkCurrent() const { return sparkCurrent; }
        int getCylinderAmt() const { return cylinderAmt; }
        double getOilAmt() const { return oilAmt; }
        double getEngineSize() const { return engineSize; }
};