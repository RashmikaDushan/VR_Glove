#include "Potentiometer.h"

Potentiometer::Potentiometer(int potentiometerPin) // Initialize the sensor
{
    value = 0;
    minValue = 4095; // set opposite for callibration
    maxValue = 0;
    this->pin = potentiometerPin;
    analogReadResolution(12);
    pinMode(pin, INPUT);
}

Potentiometer::~Potentiometer()
{
    // destructor
}

void Potentiometer::calibrateMaxValue(){ // calibrate the maximum value of sensor
    value = analogRead(pin);
    if (value > this->maxValue){
        maxValue = value;
    }
}

void Potentiometer::calibrateMinValue(){ // calibrate the minimum value of sensor
    value = analogRead(pin);
    if (value < this->minValue){
        minValue = value;
    }
}

int Potentiometer::readValue(){ // read the value of sensor
    value = analogRead(pin);
    value = map(value, minValue, maxValue, 0, 4095);
    return value;
}