#pragma once

class Oil_Filter{
    private:
        bool isOEM;
        std::string model;

    public:
        Oil_Filter();
        Oil_Filter(bool OEM, std::string m);

        // Setters
        void setOEM(bool o){ isOEM = o; }
        void setModel(std::string m){ model = m; }

        // Getters
        bool getOEM() const { return isOEM; }
        std::string getModel() const { return model; }

};