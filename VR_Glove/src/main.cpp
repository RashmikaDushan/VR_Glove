/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/esp32-mpu-6050-web-server/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Create a sensor object
Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

// Init MPU6050
void initMPU(){
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}
void setup() {
  Serial.begin(115200);
  initMPU();
}

void loop() {
  mpu.getEvent(&a, &g, &temp);
  Serial.print(a.acceleration.x);Serial.print(",");
  Serial.print(a.acceleration.y);Serial.print(",");
  Serial.print(a.acceleration.z);
  Serial.print(',');
  Serial.print(g.gyro.x);Serial.print(",");
  Serial.print(g.gyro.y);Serial.print(",");
  Serial.println(g.gyro.z);
}