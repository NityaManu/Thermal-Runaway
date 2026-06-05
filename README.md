# AI-BASED THERMAL RUNAWAY DETECTION SYSTEM FOR ELECTRIC VEHICLE BATTERIES 
AI-powered EV battery monitoring system using ESP32, sensor fusion, and CNN-based anomaly detection for early thermal runaway detection and safety alerts.
## Overview
Thermal runaway is one of the most critical safety concerns in lithium-ion batteries used in Electric Vehicles (EVs). This project presents an AI-powered battery monitoring and protection system that continuously monitors battery temperature, voltage, and current to identify unsafe operating conditions before they escalate into thermal runaway.
The system combines embedded hardware, IoT communication, machine learning, and real-time visualization to provide early warning alerts and improve battery safety.
## Features
1. Real-time monitoring of battery temperature, voltage, and current
2. ESP32-based wireless data acquisition and transmission
3. CNN-based anomaly detection for battery condition classification
4. Real-time dashboard for battery health visualization
5. Automated safety alerts for abnormal operating conditions
6. Flask-based backend for data processing and communication
7. Scalable architecture for future Battery Management System (BMS) integration
## Hardware Components
1. ESP32 Development Board
2. LM35 Temperature Sensor
3. ACS712 Current Sensor
4. Voltage Divider Circuit
5. Lithium-Ion Battery Pack
## Software Stack
1. Embedded C (ESP32)
2. Python
3. Flask
4. TensorFlow
5. HTML, CSS, JavaScript
## Working Principle
1. Sensors continuously measure battery temperature, voltage, and current.
2. ESP32 acquires sensor data and transmits it via Wi-Fi.
3. Flask backend receives and processes incoming data.
4. CNN model analyzes battery parameters and predicts battery condition.
5. Dashboard displays real-time battery metrics and status.
6. Alerts are generated when abnormal conditions are detected.
## Battery Condition Classification
SAFE

WARNING

DANGER

The classification is based on both machine learning predictions and threshold-based validation to improve reliability.
## Results
1. Achieved approximately 99.5% test accuracy in battery condition classification.
2. Real-time dashboard updates battery health metrics and system status.
3. Successfully demonstrated early detection of abnormal battery conditions.
4. Enabled proactive monitoring and warning generation for improved EV battery safety.

## Web Dashboard

