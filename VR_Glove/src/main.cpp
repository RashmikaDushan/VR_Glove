#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>
#include <ESP32Servo.h>
#include <ServoMotor.h>


void waitForKeyPress();
void calibratePotentiometers();

IMU imu;
Potentiometer potentiometer(34);
ServoMotor servo(18);

void setup() {
    Serial.begin(115200);
    waitForKeyPress();
    calibratePotentiometers();
}

void loop() {
    int potPercent = potentiometer.readValue();
    Serial.print("Bent angle: ");
    Serial.println(potPercent);
    int angle = map(potPercent, 0, 4095, 0, 180);
    angle = 180-angle;
    servo.writeAngle(angle);
    delay(1000);
}


void waitForKeyPress() {
    Serial.print("Press any key to continue");
    int i = 0;
    while (!Serial.available()) {
        delay(100);
        if(i++ % 10 == 0) {
          Serial.print(".");
        }
    }
    Serial.println();
    
    Serial.read();
    
    while (Serial.available()) {
        Serial.read();
    }
}

void calibratePotentiometers() {
  Serial.println("Calibrating Potentiometer...");
  while (true)
  {
    Serial.println("Fully rotate the potentiometer");
    waitForKeyPress();
    for (size_t i = 0; i < 30; i++)
    {
      potentiometer.calibrateMaxValue(true);
      delay(100);
    }
    Serial.println("Fully rotate the potentiometer in the opposite direction");
    waitForKeyPress();
    for (size_t i = 0; i < 30; i++)
    {
      potentiometer.calibrateMinValue(true);
      delay(100);
    }
    if (potentiometer.calibrated())
    {
      Serial.println("Calibration complete!");
      break;
    }
    Serial.println("Calibration failed, retrying...");
  }
}