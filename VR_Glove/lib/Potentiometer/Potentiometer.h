#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>


class Potentiometer
{
private:    
    int maxValue, minValue, pin;
    void calibrateMaxValue();
    void calibrateMinValue();
    float calTime = 0;

public:
    Potentiometer(int potentiometerPin);
    ~Potentiometer();
    int readValue();
    int value;
    String finger;
};
#endif
