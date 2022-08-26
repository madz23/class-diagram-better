#pragma once

class Brake{
    private:
        bool isDisk; // Otherwise disk brake or drum brake, everything else is dumb design, also needed a bool
        double brakePadThickness;
    public:
        Brake();
        Brake(bool isDisk, double brakePadThickness);

        // Setters
        void setBrakeType(std::string type){
            if(type == "disk"){
                isDisk = true;
            }
            else{
                isDisk = false;
            }
        }
        void setBrakePadThickness(double t){ brakePadThickness = t;}

        // Getters
        std::string getBrakeType() const {   
            if(isDisk == true){
                return "disk";
            }
            return "drum"; 
        }
        double getThickness() const { return brakePadThickness; }
};