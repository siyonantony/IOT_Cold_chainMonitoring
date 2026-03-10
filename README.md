<img width="1204" height="1600" alt="image" src="https://github.com/user-attachments/assets/d3bcad85-b0a2-41dd-ba32-d2d6debc46dd" />
<img width="1204" height="1600" alt="image" src="https://github.com/user-attachments/assets/781795bd-7fb2-4862-b1e2-6feaa01d09e6" />
<img width="1873" height="800" alt="image" src="https://github.com/user-attachments/assets/abb76968-e2bc-4068-aeaa-f02f2bcb33a1" />

### Overview

This project implements a **Cold Chain Monitoring System** using an ESP32 microcontroller. It continuously measures **temperature and humidity** using a DHT11 sensor and determines whether the storage environment is safe for temperature-sensitive products such as vaccines or medicines.

The system displays real-time data on an **OLED display** and uploads the readings to **ThingSpeak** for remote monitoring and analysis.

The main goal is to detect **temperature excursions above 8°C** and track the duration of exposure. Based on the exposure time, the system categorizes the condition into different risk levels.

---

### Features

* Real-time **temperature and humidity monitoring**
* **Cold chain violation detection**
* **OLED display output**
* **Cloud data logging using ThingSpeak**
* Exposure time tracking for unsafe temperatures
* Serial monitoring for debugging

---

### Hardware Requirements

* ESP32 Development Board
* DHT11 Temperature & Humidity Sensor
* SSD1306 OLED Display (128x64, I2C)
* Breadboard
* Jumper Wires
* WiFi Connection

---

### Pin Configuration

| Component  | ESP32 Pin |
| ---------- | --------- |
| DHT11 Data | GPIO 4    |
| OLED SDA   | GPIO 21   |
| OLED SCL   | GPIO 22   |
| VCC        | 3.3V      |
| GND        | GND       |

---

### Libraries Required

Install the following libraries in the Arduino IDE:

* WiFi (built-in with ESP32 board package)
* ThingSpeak
* DHT Sensor Library
* Adafruit GFX Library
* Adafruit SSD1306

---

### System Workflow

1. **Initialize Hardware**

   * Start serial communication
   * Initialize the DHT11 sensor
   * Initialize the OLED display
   * Connect to WiFi

2. **Sensor Data Acquisition**

   * Read temperature and humidity values from the DHT11 sensor.

3. **Cold Chain Evaluation**

   * Threshold temperature is set to **8°C**.
   * If temperature exceeds this threshold, the system tracks exposure time.

4. **Status Classification**

| Condition                           | Status  |
| ----------------------------------- | ------- |
| Temperature ≤ 8°C                   | SAFE    |
| Temperature > 8°C for < 30 minutes  | ALERT   |
| Temperature > 8°C for 30–60 minutes | WARNING |
| Temperature > 8°C for > 60 minutes  | DISPOSE |

5. **Display Output**

   * Temperature
   * Humidity
   * System status

6. **Cloud Logging**

   * Temperature and humidity are sent to **ThingSpeak** every 20 seconds.

---

### ThingSpeak Integration

The system uploads sensor data to a ThingSpeak channel.

**Fields Used**

| Field   | Data        |
| ------- | ----------- |
| Field 1 | Temperature |
| Field 2 | Humidity    |

Data is uploaded every **20 seconds** to comply with ThingSpeak's free tier rate limits.

---

### Example OLED Output

```
Temp: 6.5 C
Hum : 60 %
Status: SAFE
```

or

```
Temp: 10.2 C
Hum : 55 %
Status: ALERT
```

---

### Serial Monitor Output Example

```
Temp: 7.2 C | Hum: 63 % | Status: SAFE
Temp: 9.1 C | Hum: 61 % | Status: ALERT
Temp: 9.3 C | Hum: 59 % | Status: WARNING
```

---

### Key Variables

| Variable        | Purpose                                                            |
| --------------- | ------------------------------------------------------------------ |
| `exposureStart` | Stores the timestamp when temperature exceeds threshold            |
| `highTemp`      | Tracks whether the system is currently in a high temperature state |
| `status`        | Determines safety state of cold chain                              |

---

### Applications

* Vaccine storage monitoring
* Pharmaceutical cold storage
* Food cold chain monitoring
* Refrigerated transport tracking

---

### Possible Improvements

* Add **SMS or email alerts**
* Use **DHT22 for higher accuracy**
* Add **buzzer alarm**
* Implement **data visualization dashboards**
* Add **battery backup monitoring**

---

### Author

Cold Chain Monitoring System using ESP32 for IoT-based temperature tracking and safety monitoring.
