#include <WiFi.h>
#include <ThingSpeak.h>
#include <Arduino.h>

// Define the GPIO pin connected to the sensor's OUT pin
const int sensorPin = 25;

// Wi-Fi credentials
const char* ssid = "E308";         // Replace with your Wi-Fi SSID
const char* password = "98806829";   // Replace with your Wi-Fi password

// ThingSpeak settings
unsigned long channelID = 2771658;       // Channel ID
const char* writeAPIKey = "762I0WX8SZUMHMI4";  // Write API Key
const char* readAPIKey = "W9RF5JQJ6UKWZXVN";   // Read API Key
WiFiClient client;
unsigned long lastUpdate = 0;  // Last update timestamp
int counter = 0;               // Counter variable

void setup() {
  // Initialize the sensor pin as input
  pinMode(sensorPin, INPUT);

  // Start the serial monitor for debugging
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read the sensor value
  int sensorValue = digitalRead(sensorPin);

  // Increment the counter when the sensor goes from 0 to 1
  static int lastSensorValue = 0;
  if (lastSensorValue == 0 && sensorValue == 1) {
    counter++;  // Increment the counter
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  lastSensorValue = sensorValue;

  // Send the counter value to ThingSpeak every 21 seconds
  if (millis() - lastUpdate >= 21000) {
    lastUpdate = millis();

    // Update ThingSpeak with the current counter value
    ThingSpeak.setField(1, counter);  // Field 1 is the "Counter"
    int result = ThingSpeak.writeFields(channelID, writeAPIKey);

    if (result == 200) {
      Serial.println("Data sent to ThingSpeak successfully");
    } else {
      Serial.println("Failed to send data to ThingSpeak");
    }
  }

  delay(100);  // Small delay to allow sensor reading to stabilize
}
