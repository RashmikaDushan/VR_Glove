#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>


class Potentiometer
{
private:    
    int maxValue, minValue, pin;

public:
    Potentiometer(int potentiometerPin);
    ~Potentiometer();
    void calibrateMaxValue(bool debug = false);
    void calibrateMinValue(bool debug = false);
    int readValue();
    bool calibrated();
    int value,finger; // should implement the finger
};

#endif
