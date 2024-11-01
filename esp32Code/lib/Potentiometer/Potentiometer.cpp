#include "Potentiometer.h"
#include "IO.h"

Potentiometer::Potentiometer(int potentiometerPin, String fingerName, bool callibrateActivated) // Initialize the sensor
{
    this->percentage = 0;
    if (callibrateActivated)
    {
        this->minValue = 4095; // set opposite for callibration
        this->maxValue = 0;
    }
    else
    {
        this->minValue = 0;
        this->maxValue = 4095;
    }
    this->pin = potentiometerPin;
    this->fingerName = fingerName;
    analogReadResolution(12);
    pinMode(pin, INPUT_PULLDOWN);
}

Potentiometer::~Potentiometer()
{
    // destructor
}

void Potentiometer::calibrateMaxValue(bool debug)
{ // calibrate the maximum value of sensor
    this->percentage = analogRead(pin);
    if (this->percentage > this->maxValue)
    {
        this->maxValue = this->percentage;
        if (debug)
        {
            Serial.print("Max Value: ");
            Serial.println(this->maxValue);
        }
    }
}

void Potentiometer::calibrateMinValue(bool debug)
{ // calibrate the minimum value of sensor
    this->percentage = analogRead(pin);
    if (this->percentage < this->minValue)
    {
        this->minValue = this->percentage;
        if (debug)
        {
            Serial.print("Min Value: ");
            Serial.println(this->minValue);
        }
    }
}

float Potentiometer::readValue()
{ // read the value of sensor
    this->percentage = analogRead(pin);
    if (this->percentage > this->maxValue)
    {
        this->percentage = this->maxValue;
    }
    else if (this->percentage < this->minValue)
    {
        this->percentage = this->minValue;
    }
    this->percentage = (this->percentage - this->minValue) / 4095.0;
    return this->percentage;
}

bool Potentiometer::calibrated()
{
    return this->maxValue > this->minValue;
}

void Potentiometer::calibratePotentiometer()
{
    Serial.printf("Calibrating %s finger...", this->fingerName);
    while (true)
    {
        Serial.println("Fully rotate the potentiometer");
        waitForKeyPress();
        for (size_t i = 0; i < 30; i++)
        {
            this->calibrateMaxValue(false);
            delay(100);
        }
        Serial.println("Fully rotate the potentiometer in the opposite direction");
        waitForKeyPress();
        for (size_t i = 0; i < 30; i++)
        {
            this->calibrateMinValue(false);
            delay(100);
        }
        if (this->calibrated())
        {
            Serial.println("Calibration complete!");
            break;
        }
        Serial.println("Calibration failed, retrying...");
    }
}