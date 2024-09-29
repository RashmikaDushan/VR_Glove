#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>
#include <ESP32Servo.h>
#include <ServoMotor.h>
#include <IO.h>

#define ACTIVATE_POTS 1
#define ACTIVATE_IMU 1
#define ACTIVATE_SERVO 0
#define CALIBRATE_POTS 0

#if ACTIVATE_IMU
IMU imu;
float *rotation;
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
  imu.begin();
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
  rotation = imu.returnData(false);
  Serial.print(rotation[0]);
  Serial.print(",");
  Serial.print(rotation[1]);
  Serial.print(",");
  Serial.print(rotation[2]);
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
  delay(2);
}