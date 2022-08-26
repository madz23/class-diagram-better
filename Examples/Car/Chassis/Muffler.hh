#pragma once

class Muffler{
    private:
        int baffleAmt;
        std::string baffleType;

    public:
        Muffler();
        Muffler(int bAmt, std::string bType);

        // Setters
        void setbaffleAmt(int a){ baffleAmt = a; }
        void setbaffleType(std::string t){ baffleType = t; }

        // Getters
        int getbaffleAmt() const { return baffleAmt; }
        std::string() const { return baffleType; }
};