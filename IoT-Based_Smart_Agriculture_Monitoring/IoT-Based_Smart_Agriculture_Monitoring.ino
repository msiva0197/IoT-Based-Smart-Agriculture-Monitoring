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
