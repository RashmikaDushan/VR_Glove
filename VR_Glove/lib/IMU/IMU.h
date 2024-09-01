#ifndef IMU_H
#define IMU_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class IMU
{
private:
  Adafruit_MPU6050 mpu; // Create a sensor object
  sensors_event_t a, g, temp;

public:
  IMU();
  ~IMU();
  void begin();
  void sendData(bool blt);
};

#endif
