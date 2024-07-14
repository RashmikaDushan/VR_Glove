# Force Feedback Glove Prototype

## Project Overview

This project aims to create a force feedback glove for enhanced virtual reality experiences. The initial prototype focuses on single finger tracking and force feedback using electrostatic braking technology.

## Core Components

1. ESP32 DevKit V1: Main microcontroller
2. MPU6050: 6-axis gyroscope and accelerometer
3. Electrostatic braking strips

## Key Features

### 3D Hand Tracking

The MPU6050 sensor provides 6 degrees of freedom (6DOF) motion tracking. This allows for:
- Accurate hand position and orientation in 3D space
- Real-time motion data for responsive VR interactions

### Finger Tracking

Initially focusing on a single finger:
- Flex sensors or the electrostatic brake strips itselves can be used for finger tracking

### Electrostatic Braking for Force Feedback

Electrostatic braking strips are the core of the force feedback system:
- Apply variable friction to finger movement
- Create a sense of resistance when interacting with virtual objects

#### How Electrostatic Braking Works

Thin conductive strips are placed on adjacent surfaces. When a voltage is applied, an electrostatic force is generated between the strips. This force creates friction, resisting movement. Varying the voltage controls the strength of the braking effect. Enables simulation of different object shapes in VR

### Communication

The communication handles by the ESP32:
- Receives tracking data from the MPU6050 via I2C protocol
- Processes motion data and calculates required force feedback
- Controls the voltage applied to electrostatic braking strips
- Communicate with a computer via Bluetooth for integration with VR applications

This project is in early development stages.
