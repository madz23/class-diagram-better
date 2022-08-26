#pragma once

// Horse is not vehicle and does not require any car parts
class Horse{
  private:
    double timeEaten;
    int timesPooped;
  public:
    Horse(double t, int p);
    Horse();

    //Setters
    void setWhenAte(double t){ timeEaten = t; }
    void setTimesPooped(int p){ timesPooped = p; }

    // Getters
    double getLastTimeEaten() const { return timeEaten; }
    int getTimesPooped() const { return timesPooped; }
}
