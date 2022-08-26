#pragma once

class Distributor{
    private:
        int contactNum;
        double watts;

    public:
        Distributor();
        Distributor(int n, double w);

        // Setters
        void setContactNum(int cN){ contactNum = cN; }
        void setWatts(double w){ watts = w; }

        // Getters
        int getcontactNum() const { return contactNum; }
        double getWatts() const { return watts; }
};