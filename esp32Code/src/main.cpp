#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>
#include <ESP32Servo.h>
#include <ServoMotor.h>
#include <IO.h>
#include "Wire.h"

#define ACTIVATE_POTS 0
#define ACTIVATE_IMU 1
#define ACTIVATE_SERVO 0
#define CALIBRATE_POTS 0

#if ACTIVATE_IMU
TwoWire wire = TwoWire(0);
TwoWire wire1 = TwoWire(1);
IMU imu(0x68, &wire);
IMU imu1(0x69, &wire);
IMU imu2(0x68, &wire1);
float *rotation;
float *rotation1;
float *rotation2;
#endif

#if ACTIVATE_POTS
Potentiometer indexFinger(34, "index", CALIBRATE_POTS);
Potentiometer middleFinger(35, "middle", CALIBRATE_POTS);
Potentiometer ringFinger(32, "ring", CALIBRATE_POTS);
Potentiometer pinkyFinger(33, "pinky", CALIBRATE_POTS);
float indexPercent, middlePercent, ringPercent, pinkyPercent;
#endif

#if ACTIVATE_SERVO
ServoMotor servo(18);
#endif

void setup()
{
  Serial.begin(115200);
#if ACTIVATE_IMU
  wire.begin(21, 22, 100000);
  wire1.begin(16, 17, 100000);
  imu.begin();
  imu1.begin();
  imu2.begin();
#endif

#if ACTIVATE_POTS && CALLIBRATE_POTS
  waitForKeyPress();
  indexFinger.calibratePotentiometer();
  middleFinger.calibratePotentiometer();
  ringFinger.calibratePotentiometer();
  pinkyFinger.calibratePotentiometer();
#endif
}

void loop()
{
  Serial.println("");
#if ACTIVATE_IMU
  Serial.print("IMU 01 : ");
  rotation = imu.returnData(false);
  Serial.print(rotation[0]);
  Serial.print(" ");
  Serial.print(rotation[1]);
  Serial.print(" ");
  Serial.print(rotation[2]);

  Serial.print(" |  IMU 02 : ");
  rotation1 = imu1.returnData(false);
  Serial.print(rotation1[0]);
  Serial.print(" ");
  Serial.print(rotation1[1]);
  Serial.print(" ");
  Serial.print(rotation1[2]);

  Serial.print(" |  IMU 03 : ");
  rotation2 = imu2.returnData(false);
  Serial.print(rotation2[0]);
  Serial.print(" ");
  Serial.print(rotation2[1]);
  Serial.print(" ");
  Serial.print(rotation2[2]);
#endif
#if ACTIVATE_POTS
  indexPercent = indexFinger.readValue();
  middlePercent = middleFinger.readValue();
  ringPercent = ringFinger.readValue();
  pinkyPercent = pinkyFinger.readValue();
  // Serial.print("Bent angle: ");
  Serial.print(",");
  Serial.print(indexPercent);
  Serial.print(",");
  Serial.print(middlePercent);
  Serial.print(",");
  Serial.print(ringPercent);
  Serial.print(",");
  Serial.print(pinkyPercent);
#endif
  // int angle = map(potPercent, 0, 4095, 0, 180);
  // angle = 180 - angle;
  // servo.writeAngle(angle);
  delay(10);
}