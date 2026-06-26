# 🏗️ System Design & Architecture

## System Overview

The Smart City Noise Level Monitoring System is built around a **sensor-microcontroller-cloud pipeline**. Sound is captured by the KY-038 sensor, processed by the Arduino Uno, displayed on LCD, and transmitted to ThingSpeak cloud via the ESP8266 Wi-Fi module.

---

## System Block Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                          SYSTEM OVERVIEW                        │
│                                                                 │
│  ┌─────────┐   Analog   ┌───────────┐  Data   ┌─────────────┐  │
│  │  KY-038 │──────────▶│  Arduino  │────────▶│   ESP8266   │  │
│  │  Sound  │            │    Uno    │         │  Wi-Fi Mod  │  │
│  │  Sensor │            │(ATmega328)│         └──────┬──────┘  │
│  └─────────┘            └─────┬─────┘                │         │
│                               │                      │ Internet│
│  ┌─────────┐   Signals        │                      ▼         │
│  │  Power  │──────────────────┤               ┌────────────┐   │
│  │ Supply  │                  │               │ThingSpeak  │   │
│  │ (7805)  │            ┌─────▼──────┐        │   Cloud    │   │
│  └─────────┘            │  16x2 LCD  │        └─────┬──────┘   │
│                         │  Display   │              │          │
│                         └────────────┘        ┌─────▼──────┐   │
│                                               │Web Dashboard│   │
│  ┌──────┐  ┌─────┐                            │ & Graphs   │   │
│  │Buzzer│  │ LED │ ◀── Alert Pins (3, 4)       └────────────┘   │
│  └──────┘  └─────┘                                             │
└─────────────────────────────────────────────────────────────────┘
```

---

## Data Flow

```
START
  │
  ▼
Setup():
  - Initialize LCD (16x2)
  - Initialize Serial (9600 baud)
  - Initialize SoftwareSerial for ESP8266
  - Connect to Wi-Fi via AT commands
  │
  ▼
loop() [repeats every 1 second]:
  │
  ├── 1. readSoundLevel()
  │         - Take 10 ADC samples from KY-038 (A0)
  │         - Average the readings
  │         - Return averaged noise value (0–1023)
  │
  ├── 2. Display on LCD Row 1
  │         - "Noise: XXX"
  │
  ├── 3. Compare with threshold (default: 500)
  │         │
  │         ├── soundValue > threshold?
  │         │       YES → Buzzer ON, LED ON
  │         │             LCD Row 2: "Noise Pollution!"
  │         │             Serial: "ALERT: High Noise Detected!"
  │         │
  │         └── soundValue ≤ threshold?
  │                 YES → Buzzer OFF, LED OFF
  │                        LCD Row 2: "Normal Noise"
  │                        Serial: "Normal"
  │
  ├── 4. uploadTimer++
  │         Every 15 seconds:
  │           - Open TCP connection to ThingSpeak
  │           - Send HTTP GET with noise value to Field 1
  │           - Close connection
  │
  └── 5. delay(1000) → next cycle
```

---

## Component Roles

### Arduino Uno (ATmega328)
The central controller. Reads analog signals from the sound sensor via its 10-bit ADC (pins A0–A5), computes the noise level, controls LCD display, triggers the buzzer and LED, and sends data to the ESP8266.

### KY-038 Sound Sensor
An electret microphone with an internal amplifier and peak detector. Its **analog output (AO)** produces a voltage (0–5V) proportional to the sound intensity in the environment. Connected to Arduino pin A0. The ADC converts this to a value between 0 and 1023.

### 16x2 LCD (HD44780)
Displays two lines of 16 characters each. Operated in **4-bit mode** using 7 Arduino pins (RS, EN, D4, D5, D6, D7). Shows real-time noise level and status message.

### ESP8266 ESP-01
A Wi-Fi module that communicates with Arduino via **SoftwareSerial AT commands**. It connects to a Wi-Fi router and sends HTTP GET requests to the ThingSpeak API to upload the noise level to the cloud.

### Buzzer & LED
Digital output devices triggered when noise exceeds the threshold. Buzzer (pin 3) produces an audible alert; LED (pin 4) provides a visual indicator.

### IC 7805 Power Supply
Provides a stable **5V regulated DC** output from the 9V transformer output. The bridge rectifier (4x 1N4007 diodes) and filter capacitor (1000µF) ensure smooth DC before voltage regulation.

---

## ThingSpeak Data Architecture

```
Arduino → (HTTP GET) → ThingSpeak API → Channel Field 1 (Noise Level)
                                              │
                          ┌───────────────────┤
                          │                   │
                    Line Chart           Data Export
                    (Real-time)          (.csv / .json)
```

- **Channel Field 1**: Noise Level (ADC value, 0–1023)
- **Update interval**: Minimum 15 seconds (ThingSpeak free tier limit)
- **Data retention**: 1 year on free plan

---

## Noise Level Scale

| ADC Value | Approximate dB | Condition | System Response |
|---|---|---|---|
| 0 – 200 | Very Quiet (< 40dB) | Silent environment | Normal — No alert |
| 200 – 400 | Quiet (40–60dB) | Normal conversation | Normal — No alert |
| 400 – 500 | Moderate (60–70dB) | Busy road, office | Normal — No alert |
| 500 – 700 | Loud (70–85dB) | Traffic, machinery | **ALERT triggered** |
| 700 – 1023 | Very Loud (> 85dB) | Industrial noise | **ALERT triggered** |

> Note: ADC-to-dB mapping is approximate and depends on sensor calibration.

---

## Software State Machine

```
          ┌─────────────────────────────────────┐
          │              IDLE                   │
          │  (Reading sensor every 1 second)    │
          └──────────────┬──────────────────────┘
                         │
              ┌──────────▼──────────┐
              │    Noise ≤ 500?     │
              └──────┬────────┬─────┘
                     │        │
                   YES        NO
                     │        │
              ┌──────▼───┐ ┌──▼──────────┐
              │  NORMAL  │ │    ALERT    │
              │ LED OFF  │ │  LED ON     │
              │Buzz OFF  │ │  Buzz ON    │
              │LCD:Normal│ │LCD:Pollution│
              └──────────┘ └─────────────┘
                     │        │
                     └────────┘
                          │
                   Every 15 sec:
                   Upload to ThingSpeak
```
