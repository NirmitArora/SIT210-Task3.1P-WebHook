#include <WiFiNINA.h>
#include <ThingSpeak.h>  // ThingSpeak library

const int ldrAnalogPin = A0; // Analog pin connected to the DO pin of the LDR sensor

char ssid[] = "Galaxy M314C7C";  // WiFi SSID
char pass[] = "12345678";     // WiFi Password

unsigned long channelID = 2249574;        // My ThingSpeak Channel ID
const char *apiKey = "XT9H2S6HI7U6WICT";  // My ThingSpeak API Key

WiFiClient client;

void setup() {
  Serial.begin(9600);
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  delay(3000);  // Wait for a few seconds between readings
  int analogValue = analogRead(ldrAnalogPin);
  Serial.print("Analog Value: ");
  Serial.println(analogValue);
  delay(1000);  // Delay for a second before taking another reading
  if (!isnan(analogValue))
   {
    sendDataToThingSpeak(analogValue);
  } else 
  {
    Serial.println("Failed to read from LDR ");
  }

}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Connected to WiFi");
}

void sendDataToThingSpeak(float light) {
  ThingSpeak.setField(1, light);      // Set field 1 with light intensity data

  int httpCode = ThingSpeak.writeFields(channelID, apiKey);

  if (httpCode == 200) {
    Serial.println("Data sent to ThingSpeak");
  } else {
    Serial.println("Error sending data to ThingSpeak");
  }
}