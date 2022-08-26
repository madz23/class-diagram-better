#pragma once

class Catalytic_Converter{
    private:
        std::vector<std::string> composition;

    public:
        Catalytic_Converter();
        Catalytic_Converter(std::vector<std::string> composition);

        // Setters
        void setComposition(std::vector<std::string> c){
            composition = c;
        }

        // Getters
        std::vector<std::string> getComposition() const { return composition; }
}