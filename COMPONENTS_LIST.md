# 🧰 Components List — Bill of Materials (BOM)

## Main Components

| S.No | Component | Model / Spec | Quantity | Purpose |
|---|---|---|---|---|
| 1 | Microcontroller Board | Arduino Uno (ATmega328, 16MHz) | 1 | Main processing unit |
| 2 | Sound Sensor Module | KY-038 Microphone Sensor | 1 | Detects ambient noise |
| 3 | LCD Display | 16x2 Alphanumeric (HD44780) | 1 | Local noise level display |
| 4 | Wi-Fi Module | ESP8266 ESP-01 | 1 | Cloud data transmission |
| 5 | Active Buzzer | 5V Active Buzzer | 1 | Audio alert on high noise |
| 6 | LED | 5mm Red LED | 1 | Visual alert indicator |
| 7 | Voltage Regulator IC | IC 7805 (5V, 1A) | 1 | Regulated 5V power supply |
| 8 | Transformer | 230V to 9V Step-Down | 1 | AC mains voltage reduction |

## Passive Components

| S.No | Component | Specification | Quantity | Purpose |
|---|---|---|---|---|
| 1 | Resistor | 220Ω, 1/4W | 1 | LED current limiting |
| 2 | Resistor | 1kΩ, 1/4W | 1 | Voltage divider (ESP RX) |
| 3 | Resistor | 2.2kΩ, 1/4W | 1 | Voltage divider (ESP RX) |
| 4 | Potentiometer | 10kΩ | 1 | LCD contrast adjustment |
| 5 | Capacitor | 1000µF / 25V Electrolytic | 1 | Power supply filter |
| 6 | Capacitor | 100nF / 0.1µF Ceramic | 2 | Decoupling / bypass |
| 7 | Diode | 1N4007 (1A, 1000V) | 4 | Bridge rectifier |

## Wiring & Connectivity

| S.No | Item | Specification | Quantity |
|---|---|---|---|
| 1 | Jumper Wires | Male-to-Male, 20cm | 20 |
| 2 | Jumper Wires | Male-to-Female, 20cm | 10 |
| 3 | Breadboard | 400-point Mini Breadboard | 1 |
| 4 | USB Cable | Type A to Type B (Arduino) | 1 |

## Tools Required

| S.No | Tool | Purpose |
|---|---|---|
| 1 | Soldering Iron | Permanent connections |
| 2 | Solder Wire | Joining components |
| 3 | Multimeter | Testing voltage, continuity |
| 4 | Wire Stripper | Preparing wires |
| 5 | Screwdriver Set | Enclosure assembly |

## Software & Accounts

| S.No | Software | Version | Cost |
|---|---|---|---|
| 1 | Arduino IDE | 1.8.x or 2.x | Free |
| 2 | ThingSpeak Account | — | Free |
| 3 | Arduino Libraries | LiquidCrystal (built-in), SoftwareSerial (built-in) | Free |

---

## KY-038 Sound Sensor — Technical Details

| Parameter | Value |
|---|---|
| Operating Voltage | 3.3V – 5V |
| Output Type | Analog (AO) + Digital (DO) |
| Microphone Type | Electret Condenser |
| Frequency Response | 50Hz – 16kHz |
| Signal Output | Analog voltage proportional to sound intensity |
| Sensitivity | Adjustable via onboard potentiometer |
| PCB Size | ~36mm x 15mm |

---

## ESP8266 ESP-01 — Technical Details

| Parameter | Value |
|---|---|
| CPU | 32-bit Tensilica Xtensa L106 @ 80MHz |
| Operating Voltage | 3.3V |
| Wi-Fi Standard | IEEE 802.11 b/g/n |
| RAM | 64KB instruction, 96KB data |
| Flash Memory | 512KB – 4MB |
| GPIO Pins | 2 (GPIO 0 and GPIO 2) |
| UART | 1 (TX/RX) |
| Security | WEP, WPA, WPA2 |

---

## Arduino Uno (ATmega328) — Technical Details

| Parameter | Value |
|---|---|
| Microcontroller | ATmega328P |
| Operating Voltage | 5V |
| Input Voltage (Recommended) | 7V – 12V |
| Digital I/O Pins | 14 (6 PWM) |
| Analog Input Pins | 6 (10-bit ADC) |
| Flash Memory | 32KB |
| SRAM | 2KB |
| EEPROM | 1KB |
| Clock Speed | 16MHz |
| USB Interface | ATmega16U2 |
