#pragma once

class Air_Filter{
    private:
        bool isOEM;
        std::string model;

    public:
        Air_Filter();
        Air_Filter(bool OEM, std::string m);

        // Setters
        void setOEM(bool o){ isOEM = o; }
        void setModel(std::string m){ model = m; }

        // Getters
        bool getOEM() const { return isOEM; }
        std::string getModel() const { return model; }

};