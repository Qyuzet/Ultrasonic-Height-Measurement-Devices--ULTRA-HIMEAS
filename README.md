# ULTRA HIMEAS: Ultrasonic Height Measurement Device

## Overview

**ULTRA HIMEAS** is a portable device designed to accurately measure a person's height using an ultrasonic sensor combined with a gyroscope sensor for precise measurements. The device is powered by a Wemos D1 Mini microcontroller and communicates data via Wi-Fi to a mobile application developed using Kodular. The application interfaces with Firebase for data storage and retrieval, making the system efficient and user-friendly.

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/f86e9b3b-f6e8-4d4e-849d-d3cbc705514e)


## Team

- **Riki Awal Syahputra** (2120010136) - Developer Leader
- **Faza Rama Nugraha** (2120010291)

## System Analysis

The **ULTRA HIMEAS** device operates by placing an ultrasonic sensor on top of the user's head, facing the ground. The gyroscope sensor ensures that the device is level, thus providing accurate height measurements. The data is collected and processed by the Wemos D1 Mini and then transmitted via Wi-Fi to a mobile application, where it can be viewed and analyzed.

### Flow Process

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/2fa43a6d-51eb-4d2c-9582-692cd5f65d84)

1. **Power On**: Connect the device to a power source using an adapter.
2. **Wi-Fi Connection**: Establish a connection to a Wi-Fi network.
3. **App Initialization**: Open the mobile application.
4. **Measurement Setup**: Place the device on top of the user's head with the ultrasonic sensor facing the ground.
5. **Data Collection**: The ultrasonic sensor measures the distance to the ground, and the gyroscope sensor ensures the device is level.
6. **Data Transmission**: The collected data is sent to the Firebase database via Wi-Fi.
7. **Data Display**: The mobile application retrieves and displays the height measurement.

## Main Components

- **Wemos D1 Mini**: A compact microcontroller unit responsible for processing data and managing communication.
- **JSN-SR04T Ultrasonic Sensor**: Measures the distance from the device to the ground with high accuracy.
- **MPU6050 Gyroscope Sensor**: Ensures the device is level during measurement.
- **Active Buzzer**: Provides auditory feedback to indicate successful measurement or errors.
- **Breadboard**: Used for assembling and testing the electronic circuits.

## Schematic

The schematic includes detailed circuit diagrams showing the connections between the Wemos D1 Mini, the ultrasonic sensor, the gyroscope sensor, and the active buzzer. It also includes a PCB layout for a more permanent and compact assembly.

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/638810ca-4bb3-47d6-9f00-bf36074e167c)

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/541fb545-4fdd-47d4-a06b-5b7a86d67209)

### Circuit Diagram

- **Power Supply**: The Wemos D1 Mini is powered via a micro USB adapter.
- **Sensor Connections**: The JSN-SR04T ultrasonic sensor and MPU6050 gyroscope sensor are connected to the appropriate pins on the Wemos D1 Mini.
- **Buzzer Connection**: The active buzzer is connected to a digital output pin on the Wemos D1 Mini.


![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/cabaf61d-cb24-4a47-953b-7a8b175706c3)


## Code

The firmware running on the Wemos D1 Mini integrates multiple functionalities to ensure accurate and reliable measurements. Key aspects of the code include:

- **MPU6050 Integration**: Reads data from the gyroscope sensor to ensure the device is level.
- **JSN-SR04T Integration**: Measures the distance to the ground.
- **Wi-Fi & Firebase Integration**: Manages data transmission to and from the Firebase database.
- **Buzzer Control**: Provides feedback to the user through sound.
- **Measurement Algorithms**:
  - **Bubble Sort Algorithm (HST Mode)**: Calculates and displays the highest value from 100 measurements.
  - **Average Algorithm (AVG Mode)**: Calculates and displays the average value from 100 measurements.
- **Random Hash TX**: Ensures secure data transmission.

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/471acacc-fc96-4c13-93cc-ac2431315c0b)

![UME+ FLOWCHART (HARDWARE) drawio](https://github.com/Qyuzet/Ultrasonic-Height-Measurement-Devices--ULTRA-HIMEAS/assets/93258081/3b5691ac-f2e5-4bf9-ab4e-ac2641117f64)
## Software (Kodular)

The mobile application, developed using Kodular, provides an intuitive interface for interacting with the ULTRA HIMEAS device. The app features real-time data display and various modes for analyzing the measurements.

![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/9615a692-4031-4421-9e22-e7b36d25435b)
![image](https://github.com/Qyuzet/Qyuzet/assets/93258081/15e4b3ee-4339-47a5-955a-ac988bc78a34)

### Key Features

- **User Interface**: Simple and user-friendly, allowing users to input their name, select measurement modes, and view results.
- **Screen Initialization**: Sets up the initial screen and components when the app is launched.
- **Clock Management**: Handles timing functions within the app.
- **Firebase Integration**: Manages data read and update operations from the Firebase database.
- **Measurement Display**:
  - **HST Mode**: Shows the highest value from 100 measurements.
  - **AVG Mode**: Shows the average value from 100 measurements.

### Application Screens

- **Splash Screen**: Initial loading screen displaying the app logo.
- **Main Menu**: Allows users to enter their name, select the measurement mode, and start the measurement process.
- **Measurement Result**: Displays the height measurement result along with gyroscope accuracy data.

## Conclusion

The **ULTRA HIMEAS** project exemplifies the integration of embedded systems with mobile application development to create a practical and accurate height measurement device. By combining ultrasonic and gyroscope sensors with a powerful microcontroller and a robust mobile app, we have developed a system that is both reliable and user-friendly. This project not only demonstrates technical proficiency but also highlights the potential for innovative solutions in everyday applications.

For more details and updates, visit [Project Link](https://bit.ly/3DhhFww).
