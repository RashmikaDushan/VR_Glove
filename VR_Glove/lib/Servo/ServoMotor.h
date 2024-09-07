#ifndef SERVO_H
#define SERVO_H

#include <Arduino.h>
#include <ESP32Servo.h>


class ServoMotor
{
private:    
    int maxValue, minValue, pin;
    Servo servo;

public:
    ServoMotor(int servoPin);
    ~ServoMotor();
    // void calibrateMaxValue(bool debug = false); // To-do
    // void calibrateMinValue(bool debug = false);
    int writeAngle(int angle);
    // bool calibrated();
    int angle,finger; // should implement the finger
};

#endif
