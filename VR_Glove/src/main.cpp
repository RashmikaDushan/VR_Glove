#include <Arduino.h>
#include <Potentiometer.h>

int potentiometerPin = 34;

void setup() {
  Serial.begin(115200);
  Potentiometer(potentiometerPin);
}

void loop() {
  Serial.println("Potentiometer value: " + String(Potentiometer::read()));
  delay(1000);
}