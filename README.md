# 🔊 Smart City Noise Level Monitoring Using IoT Sensors

> A real-time IoT-based noise pollution monitoring system using Arduino Uno, KY-038 sound sensor, ESP8266 Wi-Fi module, and ThingSpeak cloud platform — built for smart city applications.

---

## 🎓 About the Project

| Field | Details |
|---|---|
| **Project Title** | Smart City Noise Level Monitoring Using IoT Sensors |
| **Institute** | Sree Chaitanya Institute of Technological Sciences, Karimnagar |
| **University** | Jawaharlal Nehru Technological University, Hyderabad (JNTUH) |
| **Department** | Electronics & Communication Engineering (ECE) |
| **Degree** | Bachelor of Technology (B.Tech) |
| **Batch** | 2022 – 2026 |
| **Guide** | Mrs. M. SWAPNA, Associate Professor, Dept. of ECE |

### 👥 Team Members

| Name | Roll Number |
|---|---|
| Buddula Kalyan Kumar | 22TR1A0410 |
---

## 📌 What Does This System Do?

This IoT system **continuously monitors ambient noise levels** in real time and:

- 📟 **Displays** the noise level on a 16x2 LCD at the monitoring location
- 🚨 **Triggers a buzzer & LED** when noise exceeds a safe threshold
- ☁️ **Uploads data to ThingSpeak** cloud for remote monitoring and analysis
- 📊 **Visualizes** noise trends on a web dashboard from anywhere

---

## 🛠️ Hardware Components

| Component | Model / Spec | Purpose |
|---|---|---|
| Microcontroller | Arduino Uno (ATmega328) | Main processing unit |
| Sound Sensor | KY-038 Microphone Module | Detects ambient noise |
| LCD Display | 16x2 Alphanumeric (HD44780) | Local real-time display |
| Wi-Fi Module | ESP8266 ESP-01 | Wireless data transmission |
| Buzzer | Active Buzzer | Audio alert on high noise |
| LED | 5mm LED | Visual alert indicator |
| Power Supply | IC 7805 (5V Regulated) | Stable power to all components |

---

## 💻 Software & Tools

| Tool | Purpose |
|---|---|
| Arduino IDE | Code development and upload |
| Embedded C | Programming language |
| ThingSpeak | IoT cloud platform for data storage & visualization |
| Serial Monitor | Real-time debugging output |

---

## 🗂️ Project Structure

```
Smart-City-Noise-Monitor/
│
├── noise_monitor.ino          # Main Arduino sketch (source code)
├── README.md                  # This file
├── LICENSE                    # MIT License
├── .gitignore                 # Files excluded from Git
│
├── hardware/
│   ├── CIRCUIT_DIAGRAM.md     # Circuit connections & pin mapping
│   └── COMPONENTS_LIST.md     # Full bill of materials (BOM)
│
└── docs/
    ├── SYSTEM_DESIGN.md       # Architecture, block diagram, working
    ├── SETUP_GUIDE.md         # Step-by-step hardware & software setup
    └── THINGSPEAK_GUIDE.md    # How to configure ThingSpeak cloud
```

---

## ⚡ Quick Start

### Step 1 — Hardware Setup

Connect components as follows:

**LCD (16x2) → Arduino Uno:**
```
LCD RS  → Arduino Pin 12
LCD EN  → Arduino Pin 11
LCD D4  → Arduino Pin 10
LCD D5  → Arduino Pin 9
LCD D6  → Arduino Pin 8
LCD D7  → Arduino Pin 7
LCD Vss → GND
LCD Vdd → 5V
LCD Vo  → 10kΩ Potentiometer (contrast)
LCD A   → 5V (backlight)
LCD K   → GND (backlight)
```

**Sound Sensor (KY-038) → Arduino Uno:**
```
AO (Analog Out) → Arduino A0
VCC             → 5V
GND             → GND
```

**Buzzer & LED:**
```
Buzzer (+) → Arduino Pin 3
LED (+)    → Arduino Pin 4 (with 220Ω resistor)
GND        → Arduino GND
```

**ESP8266 → Arduino:**
```
ESP TX  → Arduino Pin 5
ESP RX  → Arduino Pin 6
VCC     → 3.3V
GND     → GND
```

---

### Step 2 — Configure the Code

Open `noise_monitor.ino` in Arduino IDE and update these lines:

```cpp
// ThingSpeak API Key (from your ThingSpeak channel)
const String THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";  // ← Replace

// Wi-Fi credentials
espSerial.println("AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"");  // ← Replace
```

Adjust the noise threshold if needed:
```cpp
int threshold = 500;   // ADC value (0–1023); increase to make less sensitive
```

---

### Step 3 — Upload to Arduino

1. Open Arduino IDE
2. Go to `File → Open → noise_monitor.ino`
3. Select Board: `Tools → Board → Arduino Uno`
4. Select Port: `Tools → Port → COM3` (or your port)
5. Click **Upload** (→ arrow button)

---

### Step 4 — Monitor Output

Open `Tools → Serial Monitor` at **9600 baud** to see live output:

```
=== Smart City Noise Monitor ===
System Initializing...
Connecting to Wi-Fi...
Wi-Fi Connected!
Setup complete. Monitoring started.
--------------------------------
Noise Level: 312  |  Status: Normal
Noise Level: 287  |  Status: Normal
Noise Level: 634  |  Status: ALERT: High Noise Detected!
Noise Level: 589  |  Status: ALERT: High Noise Detected!
Noise Level: 301  |  Status: Normal
```

---

## 📟 LCD Display Output

**Normal condition:**
```
┌────────────────┐
│ Noise:312      │
│ Normal Noise   │
└────────────────┘
```

**High noise alert:**
```
┌────────────────┐
│ Noise:634      │
│ Noise Pollution│
└────────────────┘
```

---

## ☁️ ThingSpeak Cloud Setup

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Create a new **Channel** with Field 1 labeled "Noise Level"
3. Copy your **Write API Key** from the API Keys tab
4. Paste it into `noise_monitor.ino` where indicated
5. View live charts at: `https://thingspeak.com/channels/YOUR_CHANNEL_ID`

---

## ⚙️ Customization

### Change Noise Threshold
```cpp
int threshold = 500;   // Increase = less sensitive, Decrease = more sensitive
```

### Change Upload Interval
```cpp
int uploadInterval = 15;   // Seconds between ThingSpeak uploads (minimum: 15)
```

### Change Averaging Samples
```cpp
int sampleCount = 10;   // More samples = smoother readings, slightly slower
```

---

## 📋 Requirements

**Hardware:**
- Arduino Uno
- KY-038 Sound Sensor Module
- 16x2 LCD Display
- ESP8266 ESP-01 Wi-Fi Module
- Active Buzzer
- LED + 220Ω Resistor
- 10kΩ Potentiometer (for LCD contrast)
- 5V Regulated Power Supply
- Jumper wires and breadboard

**Software:**
- Arduino IDE (v1.8.x or 2.x)
- ThingSpeak account (free)
- Active Wi-Fi connection

---

## 🔮 Future Scope

- [ ] GPS integration for noise pollution mapping
- [ ] Mobile application for real-time alerts
- [ ] AI/ML for noise pattern prediction
- [ ] Solar-powered deployment
- [ ] Multi-node city-wide sensor network
- [ ] Integration with air quality and temperature sensors
- [ ] Automated SMS/email alerts via Twilio or SendGrid

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgements

i'm express My sincere gratitude to:
- **Mrs. M. SWAPNA**, Associate Professor, Dept. of ECE, SCITS — for constant guidance and supervision
- **Dr. V. PRAVEEN KUMAR**, Professor & HOD, Dept. of ECE, SCITS — for encouragement and facilities
- **Dr. A. PRASAD RAJU**, Principal, SCITS — for providing the infrastructure needed for this project

---

## 📚 References

1. A. Kumar and B. Singh, "IoT Based Noise Pollution Monitoring System," *IJERT*, vol. 8, no. 5, 2019.
2. Arduino Official Documentation — [arduino.cc](https://www.arduino.cc)
3. ESP8266 Datasheet — Espressif Systems
4. WHO, "Guidelines for Community Noise," 1999.
5. ThingSpeak IoT Platform — [thingspeak.com](https://thingspeak.com)

---

⚠️ **Disclaimer:** This project is built for academic and educational purposes only.

<p align="center">Made with ❤️ by Kalyan Kumar  | SCITS Karimnagar | ECE Dept. | 2022–2026</p>
