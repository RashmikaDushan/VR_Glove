#include "Potentiometer.h"

class Potentiometer
{
private:    
    int maxValue, minValue, pin;
    void calibrateMaxValue();
    void calibrateMinValue();
    float calTime = 0;

public:
    int readValue;
    String finger;
    Potentiometer(int pin);
    ~Potentiometer();
    int read();
};

Potentiometer::Potentiometer(int pin) // Initialize the sensor
{
    readValue = 0;
    minValue = 4095; // set opposite for callibration
    maxValue = 0;
    this->pin = pin;
    analogReadResolution(12);
    pinMode(pin, INPUT);
}

Potentiometer::~Potentiometer()
{
    // destructor
}

void Potentiometer::calibrateMaxValue(){ // calibrate the maximum value of sensor
    readValue = analogRead(pin);
    if (readValue > this->maxValue){
        maxValue = readValue;
    }
}

void Potentiometer::calibrateMinValue(){ // calibrate the minimum value of sensor
    readValue = analogRead(pin);
    if (readValue < this->minValue){
        minValue = readValue;
    }
}

int Potentiometer::read(){ // read the value of sensor
    readValue = analogRead(pin);
    readValue = map(readValue, minValue, maxValue, 0, 4095);
    return readValue;
}