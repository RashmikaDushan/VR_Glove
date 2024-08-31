#include "IMU.h"

class IMU
{
private:
  Adafruit_MPU6050 mpu; // Create a sensor object
  sensors_event_t a, g, temp;

public:
  IMU();
  ~IMU();
  void sendData(bool blt);
};

IMU::IMU()
{
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050");
    while (1) {
      delay(10); // Infinite loop
    }
  }
  Serial.println("MPU6050 initialized!");
}

IMU::~IMU()
{
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