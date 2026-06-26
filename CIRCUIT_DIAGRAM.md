# 🔌 Circuit Diagram & Pin Connections

## System Block Diagram

```
┌──────────────┐     Analog Signal      ┌─────────────────┐
│  KY-038      │ ─────────────────────▶ │                 │
│  Sound Sensor│                        │   Arduino Uno   │
└──────────────┘                        │  (ATmega328)    │
                                        │                 │
┌──────────────┐     Digital Signals    │                 │
│  Power Supply│ ─────────────────────▶ │                 │
│   (IC 7805)  │     5V Regulated       │                 │
└──────────────┘                        └────────┬────────┘
                                                 │
                    ┌────────────────────────────┤
                    │              │             │
              LCD Display      Buzzer + LED   ESP8266
              (16x2 HD44780)  (Alert Output)  Wi-Fi Module
                    │              │             │
              Local Display    Audio/Visual   ThingSpeak
              of Noise Level     Alert        Cloud Upload
```

---

## Pin Mapping Table

### LCD 16x2 → Arduino Uno

| LCD Pin | LCD Symbol | Arduino Pin | Notes |
|---|---|---|---|
| 1 | Vss (GND) | GND | Ground |
| 2 | Vdd (+5V) | 5V | Power |
| 3 | Vo (Contrast) | Middle of 10kΩ pot | Adjust for contrast |
| 4 | RS | Pin 12 | Register Select |
| 5 | R/W | GND | Always write mode |
| 6 | EN | Pin 11 | Enable |
| 7–10 | DB0–DB3 | Not connected | 4-bit mode |
| 11 | DB4 | Pin 10 | Data bit 4 |
| 12 | DB5 | Pin 9 | Data bit 5 |
| 13 | DB6 | Pin 8 | Data bit 6 |
| 14 | DB7 | Pin 7 | Data bit 7 |
| 15 | A (Backlight +) | 5V | Backlight |
| 16 | K (Backlight –) | GND | Backlight |

---

### KY-038 Sound Sensor → Arduino Uno

| Sensor Pin | Arduino Pin | Notes |
|---|---|---|
| AO (Analog Out) | A0 | Analog noise level signal |
| DO (Digital Out) | Not used | Optional threshold output |
| VCC | 5V | Power |
| GND | GND | Ground |

> 💡 **Note:** Use the **AO** (Analog Output) pin — it gives a continuous analog voltage proportional to sound intensity. The DO pin only gives HIGH/LOW based on a preset potentiometer threshold.

---

### Buzzer → Arduino Uno

| Buzzer Pin | Arduino Pin | Notes |
|---|---|---|
| + (Positive) | Pin 3 | Digital output |
| – (Negative) | GND | Ground |

---

### LED Indicator → Arduino Uno

| LED Pin | Arduino Pin | Notes |
|---|---|---|
| Anode (+) | Pin 4 (via 220Ω) | Digital output |
| Cathode (–) | GND | Ground |

> ⚠️ Always use a **220Ω current-limiting resistor** in series with the LED to prevent burning it out.

---

### ESP8266 ESP-01 → Arduino Uno

| ESP8266 Pin | Arduino Pin | Notes |
|---|---|---|
| TX | Pin 5 (RX of SoftSerial) | ESP sends data |
| RX | Pin 6 (TX of SoftSerial) | Arduino sends AT commands |
| VCC | 3.3V | ⚠️ Must use 3.3V NOT 5V |
| GND | GND | Ground |
| CH_PD (EN) | 3.3V | Enable pin — must be HIGH |
| RST | 3.3V (or float) | Reset pin |

> ⚠️ **IMPORTANT:** ESP8266 operates at **3.3V logic level**. Do NOT connect it directly to Arduino's 5V pins — it will damage the module. Use a voltage divider or logic level converter on the RX line of ESP8266.

**Voltage divider for ESP RX line (5V → 3.3V):**
```
Arduino Pin 6 ── 1kΩ ──┬── ESP8266 RX
                        │
                       2.2kΩ
                        │
                       GND
```

---

## Power Supply (IC 7805)

```
AC Mains (230V)
     │
     ▼
Step-Down Transformer (230V → 9V AC)
     │
     ▼
Bridge Rectifier (4x Diodes — 1N4007)
     │
     ▼
Filter Capacitor (1000µF / 25V)
     │
     ▼
IC 7805 Voltage Regulator
     │
     ▼
5V DC Regulated Output → Arduino 5V / LCD / Sensors
```

### IC 7805 Specifications

| Parameter | Value |
|---|---|
| Output Voltage | 5V |
| Input Voltage Range | 7V – 35V |
| Maximum Output Current | 1A |
| Operating Temperature | 0°C – 125°C |
| Vin – Vout Difference | 5V – 20V |

---

## Full Circuit Summary

```
230V AC ──▶ Transformer ──▶ Rectifier ──▶ Filter ──▶ IC 7805 ──▶ 5V DC
                                                                     │
                          ┌──────────────────────────────────────────┤
                          │              │           │               │
                     Arduino Uno    KY-038 Sensor  16x2 LCD       ESP8266
                          │              │           │            (3.3V)
                       Pin 3 ──────▶ Buzzer
                       Pin 4 ──────▶ LED
                       A0   ◀─────── Sound Sensor AO
                       12,11,10,9,8,7 ──▶ LCD
                       5,6  ◀──────▶ ESP8266 (SoftwareSerial)
```
