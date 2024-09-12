#include "Potentiometer.h"

Potentiometer::Potentiometer(int potentiometerPin) // Initialize the sensor
{
    percentage = 0;
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
    percentage = analogRead(pin);
    if (percentage > this->maxValue){
        maxValue = percentage;
        if (debug){
            Serial.print("Max Value: ");
            Serial.println(maxValue);
        }
    }
}

void Potentiometer::calibrateMinValue(bool debug){ // calibrate the minimum value of sensor
    percentage = analogRead(pin);
    if (percentage < this->minValue){
        minValue = percentage;
        if (debug){
            Serial.print("Min Value: ");
            Serial.println(minValue);
        }
    }
}

int Potentiometer::readValue(){ // read the value of sensor
    percentage = analogRead(pin);
    percentage = map(percentage, minValue, maxValue, 0, 4095);
    return percentage;
}

bool Potentiometer::calibrated(){
    return this->maxValue > this->minValue;
}