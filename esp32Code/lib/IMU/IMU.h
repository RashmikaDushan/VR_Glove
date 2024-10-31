#ifndef IMU_H
#define IMU_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

class IMU
{
private:
  MPU6050 mpu;
  bool dmpReady = false;
  uint8_t devStatus;
  uint16_t packetSize;
  uint8_t fifoBuffer[64];

  Quaternion q;
  VectorInt16 aa;
  VectorInt16 aaReal;
  VectorFloat gravity;
  float ypr[3] = {0, 0, 0};
  // int16_t q[4] = {0, 0, 0, 0};

public:
  IMU(uint8_t address, void *wireObj);
  ~IMU();
  void begin();
  float *returnData(bool debug);
};

#endif
