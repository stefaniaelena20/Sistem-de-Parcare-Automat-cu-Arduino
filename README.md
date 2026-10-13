# 🚗 Automatic Parking System with Arduino

An Arduino-based parking system that tracks available parking spaces and controls an entrance barrier automatically. Two ultrasonic sensors detect vehicles at the entrance and exit, while an LCD displays the current number of available spaces.

<p align="center">
  <img src="https://img.shields.io/badge/Arduino-Embedded%20Systems-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Arduino">
  <img src="https://img.shields.io/badge/C%2B%2B-Arduino%20Sketch-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
  <img src="https://img.shields.io/badge/Hardware-Ultrasonic%20Sensors%20%7C%20Servo-orange?style=for-the-badge" alt="Hardware">
</p>

## ✨ Features

- **Vehicle detection** at the entrance and exit using two ultrasonic sensors
- **Automatic barrier control** with a servo motor
- **Parking capacity tracking** for up to four vehicles
- **LCD status display** showing available spaces and parking messages
- **Full parking detection** that prevents entry when no spaces are available
- **Automatic barrier closing** after a vehicle passes
- **Serial Monitor messages** for tracking vehicle detection and system activity

## 🧰 Components and Technologies

### Hardware

- Arduino board
- 2 × HC-SR04 ultrasonic sensors
- Servo motor for the barrier
- 16 × 2 LCD with I2C interface
- Jumper wires

### Software

- **Arduino IDE**
- **C++**
- **LiquidCrystal_I2C** library
- **Servo** library

## ⚙️ How It Works

1. The entrance sensor checks for a vehicle within the configured detection range.
2. If a parking space is available, the system reduces the available-space count and opens the barrier.
3. The LCD displays a welcome message and the updated number of spaces.
4. The barrier closes automatically after the configured delay.
5. When the exit sensor detects a vehicle, the system increases the available-space count and opens the barrier for exit.
6. The LCD displays the updated parking availability.

The parking capacity is set to **4 spaces**. Vehicle detection is triggered at approximately **30 cm**, and the barrier stays open for approximately **3 seconds**.

## 🔌 Pin Connections

| Component | Arduino Pin |
|---|---:|
| Entrance sensor — TRIG | `2` |
| Entrance sensor — ECHO | `3` |
| Exit sensor — TRIG | `4` |
| Exit sensor — ECHO | `5` |
| Barrier servo signal | `11` |
| LCD I2C address | `0x27` |

Connect the sensors, servo, and LCD to the appropriate power and ground pins as well.

## 🚀 Getting Started

### Requirements

- Arduino IDE
- An Arduino-compatible board
- HC-SR04, servo, and I2C LCD libraries/components

### Upload the Program

1. Clone the repository:

   ```bash
   git clone https://github.com/stefaniaelena20/Sistem-de-Parcare-Automat-cu-Arduino.git
   cd Sistem-de-Parcare-Automat-cu-Arduino
   ```

2. Open `bun_pmp.ino` in the Arduino IDE.
3. Install the **LiquidCrystal_I2C** library if it is not already installed.
4. Connect the components according to the pin table.
5. Select your Arduino board and its port in the IDE.
6. Upload the sketch.
7. Open the Serial Monitor and set the baud rate to **9600** to view system messages.

## 📁 Project Structure

```text
Sistem-de-Parcare-Automat-cu-Arduino/
├── bun_pmp.ino    # Arduino program for sensors, display, and barrier control
└── pmp_bun.docx   # Project documentation
```

## 📚 What I Practiced

- Programming an Arduino-based system in C++
- Reading distance measurements from ultrasonic sensors
- Controlling a servo motor
- Displaying information on an I2C LCD
- Tracking state and available capacity
- Connecting hardware components with embedded software
- Testing and debugging through the Serial Monitor

## 👩‍💻 Author

**Stefania Elena Czebely**
