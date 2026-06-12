# Smart Street Light Using ESP32

## Overview

This project presents an IoT-based Smart Street Light system designed to improve energy efficiency and street lighting management. The system utilizes an ESP32 microcontroller, Infrared (IR) sensors, and a Light Dependent Resistor (LDR) sensor to automatically adjust street light operation based on environmental conditions and detected movement.

The system is integrated with the Blynk platform, enabling real-time monitoring and remote control through a mobile application.

---

## Features

* Automatic street light control based on ambient light intensity
* Motion detection using multiple IR sensors
* Dynamic LED brightness adjustment
* Energy-efficient lighting operation
* Real-time monitoring through Blynk Cloud
* Remote control using smartphone application
* WiFi-enabled IoT connectivity
* Low-cost and scalable architecture

---

## System Architecture

### Input Devices

#### Infrared (IR) Sensors

* Detect vehicle and pedestrian movement.
* Monitor multiple sections of the street.
* Trigger lighting responses when motion is detected.

#### Light Dependent Resistor (LDR)

* Measures ambient light intensity.
* Determines day and night conditions.
* Controls automatic activation of the street lighting system.

### Processing Unit

#### ESP32 DEVKIT V1

* Acts as the central controller.
* Processes data received from IR and LDR sensors.
* Controls LED street lights.
* Communicates with Blynk Cloud via WiFi.

### Output Devices

#### LED Street Lights

* Six LED lamps simulate street lighting.
* Brightness automatically adjusts based on sensor data.
* Operate in standby and active lighting modes.

### IoT Platform

#### Blynk Cloud

* Real-time monitoring dashboard.
* Remote lighting control.
* Sensor data visualization.
* Energy consumption monitoring.

---

## Components Used

* ESP32 DEVKIT V1
* 6 × Infrared (IR) Sensors
* 1 × Light Dependent Resistor (LDR)
* 6 × White LEDs
* 330 Ω Resistors
* 1 kΩ Resistor
* Battery Power Supply
* Step-Down Converter
* Blynk IoT Platform
* Jumper Wires
* PCB Board

---

## Working Principle

1. The LDR sensor continuously monitors ambient light conditions.
2. During daytime, all street lights remain off to save energy.
3. During nighttime, the system activates monitoring mode.
4. IR sensors detect the presence of vehicles or pedestrians.
5. When motion is detected, the corresponding LED increases brightness.
6. LEDs return to standby brightness when no motion is detected.
7. System status is transmitted to Blynk Cloud for monitoring and control.

---

## Technologies Used

* Arduino IDE
* C++
* ESP32
* IoT Systems
* Blynk Cloud
* Wireless Communication
* Embedded Systems
* Sensor Integration

---

## Applications

* Smart City Infrastructure
* Energy-Efficient Street Lighting
* Campus Lighting Systems
* Residential Area Lighting
* Industrial Area Lighting
* Public Road Lighting
