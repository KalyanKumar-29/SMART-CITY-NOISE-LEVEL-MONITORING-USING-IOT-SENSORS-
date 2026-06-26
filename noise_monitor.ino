/*
 =============================================================================
   Smart City Noise Level Monitoring Using IoT Sensors
 =============================================================================
   Project     : Major Project - B.Tech ECE (2022-2026)
   Institute   : Sree Chaitanya Institute of Technological Sciences, Karimnagar
   Department  : Electronics & Communication Engineering (ECE)
   University  : Jawaharlal Nehru Technological University, Hyderabad (JNTUH)
   Guide       : Mrs. M. SWAPNA, Associate Professor, Dept. of ECE

   Team Members:
     - Buddula Kalyan Kumar  (22TR1A0410)

 =============================================================================
   Hardware Components:
     - Arduino Uno (ATmega328)
     - KY-038 Microphone Sound Sensor
     - 16x2 LCD Display (HITACHI HD44780)
     - ESP8266 Wi-Fi Module
     - Buzzer (Active)
     - LED Indicator
     - 5V Regulated Power Supply (IC 7805)

   Software:
     - Arduino IDE
     - Embedded C
     - ThingSpeak IoT Platform (for cloud data upload)

   Pin Connections:
     LCD   : RS=12, EN=11, D4=10, D5=9, D6=8, D7=7
     Sound : A0
     Buzzer: D3
     LED   : D4

 =============================================================================
   Description:
     This system continuously reads noise levels from a KY-038 sound sensor
     connected to Arduino Uno. The noise level (analog ADC value) is:
       1. Displayed on a 16x2 LCD in real time
       2. Compared against a threshold (default: 500)
       3. If threshold exceeded: Buzzer & LED turn ON + "Noise Pollution!" alert
       4. If within limit: Buzzer & LED turn OFF + "Normal Noise" shown
       5. Data is also transmitted to ThingSpeak cloud via ESP8266 Wi-Fi module
 =============================================================================
*/

// ─── LIBRARY INCLUDES ────────────────────────────────────────────────────────
#include <LiquidCrystal.h>    // LCD display control
#include <SoftwareSerial.h>   // Serial communication with ESP8266

// ─── PIN DEFINITIONS ─────────────────────────────────────────────────────────
#define SOUND_SENSOR  A0      // KY-038 Analog Output → Arduino A0
#define BUZZER        3       // Active Buzzer → Digital Pin 3
#define LED           4       // LED Indicator → Digital Pin 4
#define ESP_RX        5       // ESP8266 TX → Arduino Digital Pin 5
#define ESP_TX        6       // ESP8266 RX → Arduino Digital Pin 6

// ─── LCD INITIALIZATION ──────────────────────────────────────────────────────
// LCD(RS, EN, D4, D5, D6, D7) — 4-bit mode
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// ─── ESP8266 SOFTWARE SERIAL ─────────────────────────────────────────────────
SoftwareSerial espSerial(ESP_RX, ESP_TX);

// ─── THINGSPEAK CONFIGURATION ────────────────────────────────────────────────
// Replace with your own ThingSpeak API credentials
const String THINGSPEAK_API_KEY = "YOUR_WRITE_API_KEY";  // <-- Replace this
const String THINGSPEAK_HOST    = "api.thingspeak.com";

// ─── CONFIGURATION ───────────────────────────────────────────────────────────
int threshold    = 500;       // ADC value above which noise is "too loud"
                              // Range: 0–1023 (adjust based on your environment)
int sampleCount  = 10;        // Number of ADC samples to average per reading
int uploadInterval = 15;      // Upload to ThingSpeak every N seconds (min: 15)

// ─── STATE VARIABLES ─────────────────────────────────────────────────────────
int  soundValue  = 0;         // Raw averaged ADC reading from sound sensor
int  uploadTimer = 0;         // Counts seconds since last ThingSpeak upload
bool alertActive = false;     // Tracks whether alert state is currently active

// ─── SETUP ───────────────────────────────────────────────────────────────────
void setup() {

  // Initialize Serial Monitor (for debugging)
  Serial.begin(9600);
  Serial.println("=== Smart City Noise Monitor ===");
  Serial.println("System Initializing...");

  // Initialize ESP8266 serial
  espSerial.begin(115200);

  // Configure output pins
  pinMode(BUZZER, OUTPUT);
  pinMode(LED,    OUTPUT);

  // Ensure buzzer and LED are OFF at startup
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED,    LOW);

  // Initialize LCD (16 columns, 2 rows)
  lcd.begin(16, 2);

  // ── Startup Screen ───────────────────────────────────────────────────────
  lcd.setCursor(0, 0);
  lcd.print("Noise Monitor");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();

  // ── Connect to Wi-Fi via ESP8266 ────────────────────────────────────────
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");
  connectWiFi();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Monitor Active");
  delay(1000);
  lcd.clear();

  Serial.println("Setup complete. Monitoring started.");
  Serial.println("--------------------------------");
}

// ─── MAIN LOOP ───────────────────────────────────────────────────────────────
void loop() {

  // ── 1. Read Sound Level (averaged over multiple samples) ─────────────────
  soundValue = readSoundLevel();

  // ── 2. Print to Serial Monitor ───────────────────────────────────────────
  Serial.print("Noise Level: ");
  Serial.print(soundValue);
  Serial.print("  |  Status: ");

  // ── 3. Display Noise Value on LCD Row 1 ──────────────────────────────────
  lcd.setCursor(0, 0);
  lcd.print("Noise:");
  lcd.print(soundValue);
  lcd.print("     ");     // Clear trailing characters

  // ── 4. Threshold Check and Alert Logic ───────────────────────────────────
  if (soundValue > threshold) {

    // HIGH NOISE — Trigger alert
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED,    HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Noise Pollution!");

    Serial.println("ALERT: High Noise Detected!");

    alertActive = true;

  } else {

    // NORMAL NOISE — Clear alert
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED,    LOW);

    lcd.setCursor(0, 1);
    lcd.print("Normal Noise    ");

    Serial.println("Normal");

    alertActive = false;
  }

  // ── 5. Upload to ThingSpeak every uploadInterval seconds ─────────────────
  uploadTimer++;
  if (uploadTimer >= uploadInterval) {
    uploadToThingSpeak(soundValue);
    uploadTimer = 0;
  }

  // ── 6. Wait 1 second before next reading ─────────────────────────────────
  delay(1000);
}

// ─── HELPER FUNCTION: Read Sound Level (Averaged) ────────────────────────────
/*
 * Takes multiple ADC readings from the sound sensor and returns the average.
 * Averaging reduces the effect of transient noise spikes.
 */
int readSoundLevel() {
  long total = 0;
  for (int i = 0; i < sampleCount; i++) {
    total += analogRead(SOUND_SENSOR);
    delay(5);
  }
  return (int)(total / sampleCount);
}

// ─── HELPER FUNCTION: Connect to Wi-Fi via ESP8266 ───────────────────────────
/*
 * Sends AT commands to ESP8266 to establish a Wi-Fi connection.
 * Replace "YOUR_WIFI_SSID" and "YOUR_WIFI_PASSWORD" with your credentials.
 */
void connectWiFi() {
  Serial.println("Connecting to Wi-Fi...");

  espSerial.println("AT");              // Test AT command
  delay(1000);

  espSerial.println("AT+CWMODE=1");    // Set to station mode
  delay(1000);

  // Connect to Wi-Fi — replace with your SSID and password
  espSerial.println("AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"");
  delay(5000);

  if (espSerial.find("OK")) {
    Serial.println("Wi-Fi Connected!");
    lcd.setCursor(0, 1);
    lcd.print("WiFi Connected! ");
  } else {
    Serial.println("Wi-Fi Connection Failed. Running in offline mode.");
    lcd.setCursor(0, 1);
    lcd.print("WiFi Failed     ");
  }
  delay(1500);
}

// ─── HELPER FUNCTION: Upload Data to ThingSpeak ──────────────────────────────
/*
 * Sends an HTTP GET request to ThingSpeak API with the current noise level.
 * ThingSpeak stores the value in Field 1 of your channel.
 *
 * ThingSpeak requires a minimum 15-second interval between updates.
 */
void uploadToThingSpeak(int noiseLevel) {

  Serial.print("Uploading to ThingSpeak: ");
  Serial.println(noiseLevel);

  // Open TCP connection to ThingSpeak
  String cmd = "AT+CIPSTART=\"TCP\",\"" + THINGSPEAK_HOST + "\",80";
  espSerial.println(cmd);
  delay(2000);

  if (!espSerial.find("OK")) {
    Serial.println("TCP Connection Failed.");
    return;
  }

  // Build HTTP GET request
  String httpRequest =
    "GET /update?api_key=" + THINGSPEAK_API_KEY +
    "&field1=" + String(noiseLevel) +
    " HTTP/1.1\r\nHost: " + THINGSPEAK_HOST + "\r\nConnection: close\r\n\r\n";

  // Send data length
  espSerial.print("AT+CIPSEND=");
  espSerial.println(httpRequest.length());
  delay(1000);

  // Send the HTTP request
  espSerial.print(httpRequest);
  delay(2000);

  Serial.println("Upload complete.");
}
