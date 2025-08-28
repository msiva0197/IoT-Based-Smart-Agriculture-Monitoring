# IoT-Based Smart Agriculture Monitoring System
📌 Project Overview
This project is an IoT-based Smart Agriculture Monitoring System using ESP32, Soil Moisture Sensor, and DHT22 Temperature & Humidity Sensor.
The collected data is sent to the Blynk IoT Cloud for real-time monitoring.

👉 With this project, farmers can remotely monitor:
🌡️ Temperature
💧 Humidity
🌱 Soil Moisture

🛠️ Components Required
ESP32 Development Board
DHT22 Sensor (Temperature & Humidity)
Soil Moisture Sensor
Jumper Wires + Breadboard

🔌 Circuit Diagram
⚡ Pin Connections
Soil Moisture Sensor:

VCC → 3.3V (ESP32)

GND → GND (ESP32)

AO (Analog Out) → GPIO 34 (ESP32)

DHT22 Sensor:
VCC → 3.3V (ESP32)
GND → GND (ESP32)
Data → GPIO 4 (ESP32)

💻 Source Code
#define BLYNK_TEMPLATE_ID "TMPL3Xa57J2mU"
#define BLYNK_TEMPLATE_NAME "IoT Based Smart Agriculture Monitoring"
#define BLYNK_AUTH_TOKEN  "m8BmwBPb4r99uGHsqJVoCFM4-_luP6mc"

#include <DHT.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define SOIL_PIN 34 

DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "Wokwi-GUEST";  
char pass[] = "";             

BlynkTimer timer;

void sendSensorData() {
  int soilRaw = analogRead(SOIL_PIN);
  int soilPercent = map(soilRaw, 0, 4095, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  temp = constrain(temp, -40, 80);
  hum = constrain(hum, 0, 100);

  Serial.printf("Soil Moisture: %d%%\n", soilPercent);
  Serial.printf("Temperature: %.2f°C\n", temp);
  Serial.printf("Humidity: %.2f%%\n", hum);
  Serial.println("-----------------------------");

  Blynk.virtualWrite(V1, soilPercent);
  Blynk.virtualWrite(V2, temp);
  Blynk.virtualWrite(V3, hum);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

📲 Blynk App Dashboard
V1 → Soil Moisture (%)
V2 → Temperature (°C)
V3 → Humidity (%)

📸 Output Screenshots
✅ Serial Monitor Output
✅ Blynk Dashboard Readings

🚀 Future Enhancements
Automatic irrigation using a Relay + Pump
Alert system with Push Notifications
Data logging to Google Sheets / Firebase

👨‍💻 Author
# Developed by
     # Paramasivam ✨
