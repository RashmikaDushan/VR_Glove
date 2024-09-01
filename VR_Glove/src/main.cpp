#include <Arduino.h>
#include <IMU.h>
#include <Potentiometer.h>

IMU imu;
Potentiometer potentiometer(34);

void setup() {
    Serial.begin(115200);
    imu.begin();
}

void loop() {
    int potValue = potentiometer.readValue();

    Serial.print("Accel X: ");
    imu.sendData(false);
    Serial.print(" | Pot Value: ");
    Serial.println(potValue);

    delay(1000);
}
