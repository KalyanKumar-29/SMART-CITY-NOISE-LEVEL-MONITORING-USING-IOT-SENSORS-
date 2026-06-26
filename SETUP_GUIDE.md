# 🛠️ Setup Guide — Step-by-Step Installation

## Prerequisites

Before you begin, make sure you have:

- ✅ All hardware components (see `hardware/COMPONENTS_LIST.md`)
- ✅ Arduino IDE installed on your PC
- ✅ USB Type A to Type B cable (for Arduino)
- ✅ Active Wi-Fi connection (2.4GHz — ESP8266 does NOT support 5GHz)
- ✅ ThingSpeak account (free at thingspeak.com)

---

## Step 1 — Install Arduino IDE

1. Download Arduino IDE from: https://www.arduino.cc/en/software
2. Install it on your PC (Windows / macOS / Linux)
3. Launch Arduino IDE

---

## Step 2 — Assemble the Hardware

Follow the pin connections in `hardware/CIRCUIT_DIAGRAM.md`.

**Assembly order (recommended):**
1. Build the 5V power supply on a breadboard (IC 7805 circuit)
2. Connect Arduino Uno to power
3. Connect KY-038 sound sensor to A0
4. Connect LCD display to pins 7–12 with potentiometer
5. Connect Buzzer to pin 3
6. Connect LED (with 220Ω resistor) to pin 4
7. Connect ESP8266 to pins 5 & 6 (with voltage divider on ESP RX)

> ⚠️ **Double-check all connections before powering on, especially ESP8266 voltage (must be 3.3V, NOT 5V)**

---

## Step 3 — Install Required Libraries

The project uses only **built-in Arduino libraries** — no external libraries needed!

- `LiquidCrystal.h` — pre-installed with Arduino IDE
- `SoftwareSerial.h` — pre-installed with Arduino IDE

To verify, open Arduino IDE → `Sketch → Include Library → Manage Libraries` and search for LiquidCrystal. It should already be listed as installed.

---

## Step 4 — Configure the Code

Open `noise_monitor.ino` in Arduino IDE and update these 3 things:

### 4a. ThingSpeak API Key
```cpp
const String THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";
```
Replace `YOUR_WRITE_API_KEY` with your actual ThingSpeak Write API Key.

### 4b. Wi-Fi Credentials
```cpp
espSerial.println("AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"");
```
Replace `YOUR_WIFI_SSID` with your Wi-Fi network name.
Replace `YOUR_WIFI_PASSWORD` with your Wi-Fi password.

### 4c. Noise Threshold (Optional)
```cpp
int threshold = 500;
```
Adjust this value based on your environment. Higher = less sensitive.

---

## Step 5 — Select Board and Port

1. Connect Arduino Uno to your PC via USB cable
2. In Arduino IDE:
   - `Tools → Board → Arduino AVR Boards → Arduino Uno`
   - `Tools → Port → COM3` (Windows) or `/dev/ttyUSB0` (Linux/Mac)

> If you don't see your COM port, install the Arduino drivers from: https://www.arduino.cc/en/Guide/DriverInstallation

---

## Step 6 — Upload the Code

1. Click the **Verify** button (✓) to compile — no errors should appear
2. Click the **Upload** button (→) to flash the code to Arduino
3. Wait for "Done uploading" in the status bar
4. The LCD should show "Noise Monitor / System Ready" then "Connecting WiFi"

---

## Step 7 — Open Serial Monitor

1. `Tools → Serial Monitor` (or Ctrl+Shift+M)
2. Set baud rate to **9600**
3. You should see:
```
=== Smart City Noise Monitor ===
System Initializing...
Connecting to Wi-Fi...
Wi-Fi Connected!
Setup complete. Monitoring started.
Noise Level: 312  |  Status: Normal
Noise Level: 287  |  Status: Normal
```

---

## Troubleshooting

### ❌ LCD shows nothing / blank
- Adjust the contrast potentiometer (10kΩ) slowly
- Check power connections (Vdd to 5V, Vss to GND)
- Verify RS, EN, D4–D7 pin connections

### ❌ "Wi-Fi Failed" or no response from ESP8266
- Ensure ESP8266 VCC is connected to **3.3V**, NOT 5V
- Check voltage divider on ESP8266 RX line
- Ensure CH_PD (EN) pin is connected to 3.3V
- Try lowering ESP8266 baud rate: change `espSerial.begin(115200)` to `espSerial.begin(9600)`
- Make sure your Wi-Fi is 2.4GHz (ESP8266 does not support 5GHz)

### ❌ Buzzer always ON / very sensitive
- Increase the threshold value: `int threshold = 700;`
- Reduce ambient noise near the sensor during testing

### ❌ Buzzer never triggers
- Decrease the threshold: `int threshold = 300;`
- Make loud noise near the KY-038 sensor to test

### ❌ ThingSpeak not receiving data
- Verify the API key is correct (copy from ThingSpeak → Your Channel → API Keys)
- Ensure Wi-Fi connected successfully first
- ThingSpeak free tier requires minimum 15 seconds between updates

### ❌ COM port not detected
- Install Arduino USB drivers
- Try a different USB cable (some cables are charge-only)
- Check Device Manager (Windows) for the COM port number
