#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// WiFi
const char* ssid = "CodeBlue";
const char* password = "1234567890";

// Flask server
String server = "http://10.29.43.171:5000/update";

// DHT11
#define DHTPIN 33
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Other sensors
#define VOLT_PIN 35
#define CURR_PIN 32

const float ADC_REF = 3.3;
const int ADC_RES = 4095;

float voltageDividerRatio = 11.0;
float currentOffset = 2.5;
float sensitivity = 0.185;

float readStableADC(int pin) {
  float sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / 20.0;
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected");
}

void loop() {

  // 🌡️ DHT11 Temperature
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("❌ DHT11 Read Failed");
    delay(2000);
    return;
  }

  // 🔋 Voltage
  float voltADC = readStableADC(VOLT_PIN);
  float voltage = (voltADC * ADC_REF / ADC_RES) * voltageDividerRatio;

  // ⚡ Current
  float currADC = readStableADC(CURR_PIN);
  float currVoltage = currADC * ADC_REF / ADC_RES;
  float current = (currVoltage - currentOffset) / sensitivity;

  if (abs(current) < 0.05) current = 0;

  // Send to Flask
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "temperature=" + String(temperature, 1) +
                  "&voltage=" + String(voltage, 2) +
                  "&current=" + String(current, 2);

    int response = http.POST(data);

    Serial.print("📡 Sent: ");
    Serial.print(data);
    Serial.print(" | Response: ");
    Serial.println(response);

    http.end();
  }

  Serial.print("🌡 Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | 🔋 Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | ⚡ Current: ");
  Serial.println(current);

  delay(3000);
}