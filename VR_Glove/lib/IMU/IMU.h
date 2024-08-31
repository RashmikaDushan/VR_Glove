#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class IMU {
private:
    Adafruit_MPU6050 mpu;  // Sensor object
    sensors_event_t a, g, temp;

public:
    // Constructor
    IMU();

    // Destructor
    ~IMU();

    // Method to send data
    void sendData(bool blt);
};

#endif  // IMU_H
