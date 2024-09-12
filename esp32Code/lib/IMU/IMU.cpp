#include "IMU.h"

IMU::IMU() {}

IMU::~IMU()
{
}

void IMU::begin() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050");
    while (1) {
      delay(10); // Infinite loop
    }
  }
  Serial.println("MPU6050 initialized!");
}

void IMU::sendData(bool blt) {
  mpu.getEvent(&a, &g, &temp);
  if (blt) {
    // Send data via bluetooth
  }
  else{
    Serial.print(a.acceleration.x);Serial.print(",");
    Serial.print(a.acceleration.y);Serial.print(",");
    Serial.print(a.acceleration.z);Serial.print(',');
    Serial.print(g.gyro.x);Serial.print(",");
    Serial.print(g.gyro.y);Serial.print(",");
    Serial.println(g.gyro.z);
  }
}