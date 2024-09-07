#include "ServoMotor.h"

ServoMotor::ServoMotor(int servoPin) // Initialize the sensor
{

    this->pin = servoPin;
    servo.attach(pin);
    servo.setPeriodHertz(50);
    angle = 180; // need to change
    servo.write(angle);
    // minValue = 4095; // set opposite for callibration
    // maxValue = 0;
}

ServoMotor::~ServoMotor()
{
    // destructor
}

// void ServoMotor::calibrateMaxValue(bool debug){ // calibrate the maximum value of sensor
//     value = analogRead(pin);
//     if (value > this->maxValue){
//         maxValue = value;
//         if (debug){
//             Serial.print("Max Value: ");
//             Serial.println(maxValue);
//         }
//     }
// }

// void ServoMotor::calibrateMinValue(bool debug){ // calibrate the minimum value of sensor
//     value = analogRead(pin);
//     if (value < this->minValue){
//         minValue = value;
//         if (debug){
//             Serial.print("Min Value: ");
//             Serial.println(minValue);
//         }
//     }
// }

int ServoMotor::writeAngle(int angle){ // read the value of sensor
    this->angle = angle;
    servo.write(angle);
    return angle;
}

// bool ServoMotor::calibrated(){
//     return this->maxValue > this->minValue;
// }