#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
#include <Wire.h>

class Potentiometer
{
private:    
    int maxValue, minValue, pin;
    void calibrateMaxValue();
    void calibrateMinValue();
    float calTime;

public:
    int readValue;
    String finger;
    Potentiometer(int pin);
    ~Potentiometer();
    int read();
};

#endif  // POTENTIOMETER_H