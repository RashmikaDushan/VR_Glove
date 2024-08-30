#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

String device_name = "VR_Glove";

Adafruit_MPU6050 mpu; // Create a sensor object
sensors_event_t a, g, temp; // Create a sensor event objects

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
  Serial.begin(115200); // Start the serial monitor
  initMPU(); // Initialize MPU6050
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