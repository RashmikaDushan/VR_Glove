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

void Potentiometer::calibrateMaxValue(bool debug){ // calibrate the maximum value of sensor
    value = analogRead(pin);
    if (value > this->maxValue){
        maxValue = value;
        if (debug){
            Serial.print("Max Value: ");
            Serial.println(maxValue);
        }
    }
}

void Potentiometer::calibrateMinValue(bool debug){ // calibrate the minimum value of sensor
    value = analogRead(pin);
    if (value < this->minValue){
        minValue = value;
        if (debug){
            Serial.print("Min Value: ");
            Serial.println(minValue);
        }
    }
}

int Potentiometer::readValue(){ // read the value of sensor
    value = analogRead(pin);
    value = map(value, minValue, maxValue, 0, 4095);
    return value;
}