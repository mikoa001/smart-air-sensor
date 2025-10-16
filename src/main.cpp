/**
 * Smart Air Quality Sensor
 * 
 * ESP8266-based air quality monitor with:
 * - AM2302 DHT22 (temperature & humidity)
 * - SCD40 (CO2 sensor)
 * - 3x 8x8 RGB LED matrices (NeoPixel)
 * - MQTT integration with Home Assistant
 * - USB-C powered (5V)
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Wire.h>
#include <SparkFun_SCD4x_Arduino_Library.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

// Include configuration
#include "config.h"

// Sensor objects
DHT dht(DHT_PIN, DHT_TYPE);
SCD4x scd4x;
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// LED Matrix
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(
  MATRIX_WIDTH, MATRIX_HEIGHT, LED_MATRIX_PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800
);

// Global variables
float temperature = 0.0;
float humidity = 0.0;
uint16_t co2 = 0;
unsigned long lastSensorUpdate = 0;
unsigned long lastDisplayUpdate = 0;
int displayMode = 0;  // 0=temp, 1=humidity, 2=CO2

// Color definitions
const uint16_t COLOR_TEMP = matrix.Color(255, 100, 0);    // Orange
const uint16_t COLOR_HUMIDITY = matrix.Color(0, 100, 255); // Blue
const uint16_t COLOR_CO2_GOOD = matrix.Color(0, 255, 0);   // Green
const uint16_t COLOR_CO2_WARN = matrix.Color(255, 255, 0); // Yellow
const uint16_t COLOR_CO2_BAD = matrix.Color(255, 0, 0);    // Red

void setupWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 30) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed!");
  }
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      mqttClient.publish(MQTT_TOPIC_STATUS, "online");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

void publishMQTT() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  
  char msg[50];
  
  // Publish temperature
  dtostrf(temperature, 4, 1, msg);
  mqttClient.publish(MQTT_TOPIC_TEMPERATURE, msg, true);
  Serial.print("Published temperature: ");
  Serial.println(msg);
  
  // Publish humidity
  dtostrf(humidity, 4, 1, msg);
  mqttClient.publish(MQTT_TOPIC_HUMIDITY, msg, true);
  Serial.print("Published humidity: ");
  Serial.println(msg);
  
  // Publish CO2
  sprintf(msg, "%d", co2);
  mqttClient.publish(MQTT_TOPIC_CO2, msg, true);
  Serial.print("Published CO2: ");
  Serial.println(msg);
}

void readSensors() {
  // Read DHT22
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if (!isnan(h) && !isnan(t)) {
    humidity = h;
    temperature = t;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }
  
  // Read SCD40
  if (scd4x.readMeasurement()) {
    co2 = scd4x.getCO2();
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.println(" ppm");
  } else {
    Serial.println("Failed to read from SCD40 sensor!");
  }
}

void displayValue(float value, const char* unit, uint16_t color) {
  matrix.fillScreen(0);
  matrix.setCursor(0, 0);
  matrix.setTextColor(color);
  
  char buffer[10];
  if (strcmp(unit, "ppm") == 0) {
    sprintf(buffer, "%d", (int)value);
  } else {
    dtostrf(value, 4, 1, buffer);
  }
  
  matrix.print(buffer);
  matrix.show();
}

void updateDisplay() {
  // Rotate through different measurements
  switch (displayMode) {
    case 0:  // Temperature
      displayValue(temperature, "C", COLOR_TEMP);
      break;
    case 1:  // Humidity
      displayValue(humidity, "%", COLOR_HUMIDITY);
      break;
    case 2:  // CO2
      {
        uint16_t co2Color = COLOR_CO2_GOOD;
        if (co2 > 1000) co2Color = COLOR_CO2_WARN;
        if (co2 > 2000) co2Color = COLOR_CO2_BAD;
        displayValue(co2, "ppm", co2Color);
      }
      break;
  }
  
  displayMode = (displayMode + 1) % 3;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nSmart Air Quality Sensor Starting...");
  
  // Initialize LED matrix
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.fillScreen(0);
  matrix.show();
  Serial.println("LED Matrix initialized");
  
  // Initialize DHT22
  dht.begin();
  Serial.println("DHT22 initialized");
  
  // Initialize I2C for SCD40
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("I2C initialized");
  
  // Initialize SCD40
  if (scd4x.begin() == false) {
    Serial.println("SCD40 sensor not detected. Please check wiring!");
  } else {
    Serial.println("SCD40 initialized");
    // Start periodic measurements
    scd4x.startPeriodicMeasurement();
  }
  
  // Connect to WiFi
  setupWiFi();
  
  // Setup MQTT
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  
  Serial.println("Setup complete!");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Maintain WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    setupWiFi();
  }
  
  // Maintain MQTT connection
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();
  
  // Read sensors periodically
  if (currentMillis - lastSensorUpdate >= SENSOR_UPDATE_INTERVAL) {
    lastSensorUpdate = currentMillis;
    readSensors();
    publishMQTT();
  }
  
  // Update display periodically
  if (currentMillis - lastDisplayUpdate >= DISPLAY_UPDATE_INTERVAL) {
    lastDisplayUpdate = currentMillis;
    updateDisplay();
  }
  
  delay(100);
}
