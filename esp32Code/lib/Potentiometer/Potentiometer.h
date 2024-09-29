#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

class Potentiometer
{
private:
    int maxValue, minValue, pin;

public:
    Potentiometer(int potentiometerPin, String fingerName, bool callibrateActivated);
    ~Potentiometer();
    void calibrateMaxValue(bool debug = false);
    void calibrateMinValue(bool debug = false);
    float readValue();
    bool calibrated();
    void calibratePotentiometer();
    float percentage; // should implement the finger
    String fingerName;
};

#endif
