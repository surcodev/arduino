#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

const char *ssid = "Wifi_Name";
const char *password = "B974Ab29#";
const char *scriptURL = "https://script.google.com/macros/s/AKfycbxopnGV484Jv9Px9ShOVRhDezowFzhLsnbdJwILjl2bfLGFhfQbxd_pyyP-LFc09g4o/exec"; // Google Web App URL

// DHT
const uint8_t dhtPin = 4;
const uint8_t dhtType = 11;
DHT dht(dhtPin, dhtType);

// Global variables Data
float temperature = 0.0;
float humidity = 0.0;
int aqi = 0;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi.");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    dht.begin();

    // seed the random number generator
    randomSeed(analogRead(0));
}

void loop() {
  if (readSensors()) {
    sendToDataLogger();
  }
  delay(5000);
}

bool readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Generate a random AQI value (0 to 500)
  aqi = random(0, 501);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return false;
  }

  Serial.println("Temperature: " + String(temperature));
  Serial.println("Humidity: " + String(humidity));

  return true;
}

void sendToDataLogger() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(scriptURL);
    http.addHeader("Content-Type", "application/json");

    String jsonData = String("{\"temperature\":") + temperature +
                      ",\"humidity\":" + humidity +
                      ",\"aqi\":" + aqi + "}";

    int httpResponseCode = http.POST(jsonData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.println("Error in sending data");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
