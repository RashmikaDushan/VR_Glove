#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>
#include <ESP32Servo.h>


void waitForKeyPress();
void calibratePotentiometers();

IMU imu;
Potentiometer potentiometer(34);
Servo servo;

void setup() {
    Serial.begin(115200);
    servo.attach(18);
    servo.setPeriodHertz(50);
    waitForKeyPress();
    calibratePotentiometers();
}

void loop() {
    int potValue = potentiometer.readValue();
    Serial.print("Bent angle: ");
    Serial.println(potValue);
    int angle = map(potValue, 0, 4095, 0, 180);
    servo.write(angle);
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