#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>
#include <ESP32Servo.h>
#include <ServoMotor.h>
#include <IO.h>
#include "Wire.h"

// used pins - (Wire 1) 21, 22, (Wire 2) 16, 17, (Pots) 33, 32, 35, 34, (servo1) 18 , (servo2) 19, (servo3) 2 , (servo4) 4

#define ACTIVATE_POTS 1
#define ACTIVATE_IMU 1
#define ACTIVATE_SERVO 1
#define CALIBRATE_POTS 0
#define IMU1_ACTIVED 1 // wire1 = 0x69
#define IMU2_ACTIVED 1 // wire2 = 0x68
#define IMU3_ACTIVED 0 // wire1 = 0x68
#define DEBUG 0

#if ACTIVATE_IMU
TwoWire wire1 = TwoWire(0);
TwoWire wire2 = TwoWire(1);
#if IMU1_ACTIVED
IMU imu1(0x69, &wire1);
#endif
#if IMU2_ACTIVED
IMU imu2(0x68, &wire2);
#endif
#if IMU3_ACTIVED
IMU imu3(0x68, &wire1);
#endif
float *rotation;
float *rotation1;
float *rotation2;
#endif

int closeAngle = 0;
float angleRatio = 45.0;

#if ACTIVATE_POTS
Potentiometer indexFinger(33, "index", CALIBRATE_POTS);
Potentiometer middleFinger(32, "middle", CALIBRATE_POTS);
Potentiometer ringFinger(35, "ring", CALIBRATE_POTS);
Potentiometer pinkyFinger(34, "pinky", CALIBRATE_POTS);
float indexPercent, middlePercent, ringPercent, pinkyPercent;
#endif

#if ACTIVATE_SERVO
ServoMotor servo1(18); // index
ServoMotor servo2(19); // middle
ServoMotor servo3(2); // ring
ServoMotor servo4(4); // pinky
// ServoMotor servo5(18);
int collided[5] = {0, 0, 0, 0, 0};
bool holdRestriction[5] = {0, 0, 0, 0, 0};
#endif

void setup()
{
  Serial.begin(460800);
  setCpuFrequencyMhz(240);
#if ACTIVATE_IMU
  wire1.begin(21, 22, 100000);
  wire2.begin(16, 17, 100000);

#if IMU1_ACTIVED
  imu1.begin();
#endif

#if IMU2_ACTIVED
  imu2.begin();
#endif

#if IMU3_ACTIVED
  imu3.begin();
#endif

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
#if DEBUG
#if IMU1_ACTIVED
  Serial.print("IMU 01 : ");
  rotation = imu1.returnData(false);
  Serial.print(rotation[0]);
  Serial.print(" ");
  Serial.print(rotation[1]);
  Serial.print(" ");
  Serial.print(rotation[2]);
#endif

#if IMU2_ACTIVED
  Serial.print(" |  IMU 02 : ");
  rotation1 = imu2.returnData(false);
  Serial.print(rotation1[0]);
  Serial.print(" ");
  Serial.print(rotation1[1]);
  Serial.print(" ");
  Serial.print(rotation1[2]);
#endif

#if IMU3_ACTIVED
  Serial.print(" |  IMU 03 : ");
  rotation2 = imu3.returnData(false);
  Serial.print(rotation2[0]);
  Serial.print(" ");
  Serial.print(rotation2[1]);
  Serial.print(" ");
  Serial.print(rotation2[2]);
#endif
#endif
#if !DEBUG
#if IMU1_ACTIVED
  rotation = imu1.returnData(false);
  Serial.print(rotation[0]);
  Serial.print(",");
  Serial.print(rotation[1]);
  Serial.print(",");
  Serial.print(rotation[2]);
#else 
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
#endif

#if IMU2_ACTIVED
  rotation1 = imu2.returnData(false);
  Serial.print(",");
  Serial.print(rotation1[0]);
  Serial.print(",");
  Serial.print(rotation1[1]);
  Serial.print(",");
  Serial.print(rotation1[2]);
#else 
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
#endif

#if IMU3_ACTIVED
  rotation2 = imu3.returnData(false);
  Serial.print(",");
  Serial.print(rotation2[0]);
  Serial.print(",");
  Serial.print(rotation2[1]);
  Serial.print(",");
  Serial.print(rotation2[2]);
#else 
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
  Serial.print(",");
  Serial.print("0.0");
#endif
#endif
#endif
#if ACTIVATE_POTS
  indexPercent = indexFinger.readValue();
  middlePercent = middleFinger.readValue();
  ringPercent = ringFinger.readValue();
  pinkyPercent = pinkyFinger.readValue()-0.27;
  Serial.print(",");
  Serial.print(indexPercent);
  Serial.print(",");
  Serial.print(middlePercent);
  Serial.print(",");
  Serial.print(ringPercent);
  Serial.print(",");
  Serial.print(pinkyPercent);
#endif
delay(1);
#if ACTIVATE_SERVO
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');
        int index = 0;
        while (input.length() > 0 && index < 5) {
            int commaIndex = input.indexOf(',');
            if (commaIndex == -1) {
                collided[index++] = input.toInt();
                break;
            } else {
                collided[index++] = input.substring(0, commaIndex).toInt();
                input = input.substring(commaIndex + 1);
            }
        }

      #if ACTIVATE_POTS
        if (index >= 5) {
          if (collided[0] == 1 and holdRestriction[0] == 0) {
            servo1.writeAngle(indexPercent*angleRatio);
            holdRestriction[0] = 1;
          }
          else if(collided[0] == 0 ){
            servo1.writeAngle(closeAngle);
            holdRestriction[0] = 0;
          }
                    if (collided[1] == 1 and holdRestriction[1] == 0) {
            servo1.writeAngle(indexPercent*angleRatio);
            holdRestriction[1] = 1;
          }
          else if(collided[1] == 0 ){
            servo1.writeAngle(closeAngle);
            holdRestriction[1] = 0;
          }
                    if (collided[2] == 1 and holdRestriction[2] == 0) {
            servo1.writeAngle(indexPercent*angleRatio);
            holdRestriction[2] = 1;
          }
          else if(collided[2] == 0 ){
            servo1.writeAngle(closeAngle);
            holdRestriction[2] = 0;
          }
                    if (collided[3] == 1 and holdRestriction[3] == 0) {
            servo1.writeAngle(indexPercent*angleRatio);
            holdRestriction[3] = 1;
          }
          else if(collided[3] == 0 ){
            servo1.writeAngle(closeAngle);
            holdRestriction[3] = 0;
          }
          // servo1.writeAngle(indexPercent*angleRatio);
          // if (collided[4] != 0) {
          //   servo5.writeAngle();
          // }
        }
    #endif
    }
  #endif
  delay(1);
}