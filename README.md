# Department Automation System

A Computer Organization and Assembly Language final project based on department automation. The project contains two modules: projector servo automation and smart lab occupancy indication.

## Project Overview

The aim of this project is to solve small but common problems in the department using microcontroller-based automation.

The project has two parts:

1. **Projector Servo Automation**
2. **Smart Lab Occupancy Indicator**

The first module automates the pressing of a ceiling-mounted projector power button using a servo motor. The second module displays the current availability of Lab1 using an ESP32 and a 16x2 I2C LCD.

## Modules

### 1. Projector Servo Automation

In many classrooms, projectors are mounted on the ceiling, making the power button hard to reach. This module uses an Arduino Uno, push button, and servo motor to physically press the projector button.

**Components used:**

* Arduino Uno
* Servo motor
* Push button
* Breadboard
* Jumper wires
* USB cable

**Working:**

When the push button is pressed, the Arduino moves the servo motor from its rest angle to the pressing angle. The servo presses the projector button and then returns to its original position.

### 2. Smart Lab Occupancy Indicator

Students often do not know whether a lab is free or occupied. This module uses an ESP32 and a 16x2 I2C LCD to display the status of Lab1 according to the timetable.

**Components used:**

* ESP32
* 16x2 I2C LCD
* Jumper wires
* USB cable

**Working:**

The ESP32 checks the current day and time against the stored Lab1 timetable. If a class is currently scheduled, the LCD shows the subject, section, and teacher. If the lab is free, the LCD shows the next scheduled class.

## Folder Structure

```text
department-automation-coal-project/
│
├── projector-servo-automation/
│   ├── projector_servo_automation.ino
│   ├── circuit-diagram.png
│   └── simulation-link.txt
│
├── lab-occupancy-indicator/
│   ├── lab_occupancy_indicator.ino
│   ├── circuit-diagram.png
│   └── simulation-link.txt
│
├── documentation/
    ├── final-report.pdf
    ├── flowcharts/
    ├── dfd/
    └── timetable/
```

## Software and Platforms

* Arduino IDE
* Wokwi Simulator
* ESP32 board package for Arduino IDE
* LiquidCrystal I2C library

## How to Run

### Projector Servo Automation

1. Open `projector_servo_automation.ino` in Arduino IDE.
2. Select Arduino Uno from the board menu.
3. Select the correct COM port.
4. Upload the code.
5. Press the push button to move the servo.

### Lab Occupancy Indicator

1. Open `lab_occupancy_indicator.ino` in Arduino IDE.
2. Select ESP32 Dev Module from the board menu.
3. Select the correct COM port.
4. Upload the code.
5. Connect the I2C LCD to the ESP32.
6. The LCD will show whether Lab1 is free or occupied.

## Circuit Connections

### Projector Servo Automation

| Component    | Arduino Uno Pin |
| ------------ | --------------- |
| Push Button  | D2 and GND      |
| Servo Signal | D6              |
| Servo VCC    | 5V              |
| Servo GND    | GND             |

### Smart Lab Occupancy Indicator

| LCD Pin | ESP32 Pin |
| ------- | --------- |
| VCC     | VIN / 5V  |
| GND     | GND       |
| SDA     | GPIO 21   |
| SCL     | GPIO 22   |

## COAL Relevance

This project demonstrates basic concepts of computer organization and hardware interfacing. It uses digital input, digital output, control signals, memory-stored instructions, timing, and microcontroller-based decision making.

The Arduino Uno handles push button input and servo output. The ESP32 stores timetable data, checks the current time, and sends output to an LCD display.

## Future Improvements

* Add Firebase or a web dashboard for timetable updates.
* Add RTC module for offline timekeeping.
* Add red/green LED indicators outside the lab.
* Add support for multiple labs.
* Design a proper casing for classroom deployment.
* Use an IR transmitter for projector control instead of physical pressing.

## Project Status

Prototype completed for both modules.

## Team

Aatika Yousuf
Mahnoor Shabbir
Minahil Mehmood
Mahnoor

## Project Links

* Wokwi Simulation: https://wokwi.com/projects/new/arduino-uno & https://wokwi.com/projects/new/esp32

