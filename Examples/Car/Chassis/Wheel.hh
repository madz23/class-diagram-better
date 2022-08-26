#pragma once

class Wheel{
    private:
        int diameter;
        double pressure;
        std::string rim;
    public:
        Wheel();
        Wheel(int d, double p, std::string r);

        // Setters
        void setDiameter(int d){ diameter = d; }
        void setPressure(int p){ pressure = p; }
        void setRim(std::string r){ rim = r; }

        // Getters
        int getDiameter() const { return diameter; }
        double getPressure() const { return pressure; }
        std::string getRim() const { return rim; }
};