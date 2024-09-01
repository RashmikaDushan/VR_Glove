#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>

void waitForKeyPress();

IMU imu;
Potentiometer potentiometer(34);

void setup() {
    Serial.begin(115200);
    Serial.println("Calibrating Potentiometer...");
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
    Serial.println("Calibration complete!");
}

void loop() {
    int potValue = potentiometer.readValue();
    Serial.print("Bent angle: ");
    Serial.println(potValue);
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