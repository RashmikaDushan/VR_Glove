#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>


class Potentiometer
{
private:    
    int maxValue, minValue, pin;
    float calTime = 0;

public:
    Potentiometer(int potentiometerPin);
    ~Potentiometer();
    void calibrateMaxValue(bool debug = false);
    void calibrateMinValue(bool debug = false);
    int readValue();
    int value;
    String finger;
};

#endif
