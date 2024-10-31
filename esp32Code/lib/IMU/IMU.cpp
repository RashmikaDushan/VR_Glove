#include "IMU.h"

IMU::IMU(uint8_t address, void *wireObj)
{
  this->mpu = MPU6050(address, wireObj);
}

IMU::~IMU()
{
}

void IMU::begin()
{
  // #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  // #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  //   Fastwire::setup(400, true);
  // #endif

  // Serial.begin(115200);
  while (!Serial)
    ;

  this->mpu.initialize();
  this->devStatus = this->mpu.dmpInitialize();
  Serial.print(this->devStatus);

  this->mpu.setDLPFMode(2);

  this->mpu.setXGyroOffset(220);
  this->mpu.setYGyroOffset(76);
  this->mpu.setZGyroOffset(-85);
  this->mpu.setZAccelOffset(1788);

  if (this->devStatus == 0)
  {
    this->mpu.CalibrateAccel(6);
    this->mpu.CalibrateGyro(6);
    this->mpu.setDMPEnabled(true);
    this->dmpReady = true;
    this->packetSize = this->mpu.dmpGetFIFOPacketSize();
  }
}

float *IMU::returnData(bool debug)
{
  if (this->mpu.dmpGetCurrentFIFOPacket(this->fifoBuffer))
  {
    // Display Euler angles in degrees
    this->mpu.dmpGetQuaternion(&this->q, this->fifoBuffer);
    this->mpu.dmpGetGravity(&this->gravity, &this->q);
    this->mpu.dmpGetYawPitchRoll(this->ypr, &this->q, &this->gravity);
    this->ypr[0] = this->ypr[0] * 180 / M_PI;
    this->ypr[1] = this->ypr[1] * 180 / M_PI;
    this->ypr[2] = this->ypr[2] * 180 / M_PI;
    if (debug)
    {
      Serial.printf("IMU values: %.2f,%.2f,%.2f,%.2f || ", this->q.w, this->q.x, this->q.y, this->q.z);
    }
  }
  return this->ypr;
}