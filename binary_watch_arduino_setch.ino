// Board : ESP32 Dev Module 

#include <WiFi.h>
#include "time.h"

// --- YOUR WIFI CREDENTIALS ---
const char* ssid       = "wifissid";
const char* password   = "password";

// --- TIMEZONE SETTINGS (India Standard Time) ---
const long  gmtOffset_sec = 19800; // GMT +5:30 in seconds
const int   daylightOffset_sec = 0;  // India does not use DST
const char* ntpServer = "pool.ntp.org";

// --- LED PIN DEFINITIONS ---
// Order: Most Significant Bit (Largest Value) -> Least Significant Bit (1)
// Your Hour Mapping: 8->16, 4->4, 2->2, 1->15
const int hourPins[4] = {16, 4, 2, 15};          

// Your Minute Mapping: 32->22, 16->21, 8->19, 4->18, 2->5, 1->17
const int minutePins[6] = {22, 21, 19, 18, 5, 17}; 

void setup() {
  Serial.begin(115200);

  // Initialize LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(hourPins[i], OUTPUT);
  }
  for (int i = 0; i < 6; i++) {
    pinMode(minutePins[i], OUTPUT);
  }

  // Connect to Wi-Fi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nCONNECTED!");

  // Initialize and get the time from the NTP server
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time. Check Wi-Fi connection.");
    delay(5000); // Wait 5 seconds before trying again
    return;
  }

  // Get current hour and convert to 12-hour format
  int currentHour = timeinfo.tm_hour;
  if (currentHour == 0) currentHour = 12;
  if (currentHour > 12) currentHour -= 12;
  
  // Get current minute
  int currentMinute = timeinfo.tm_min;

  // Print to Serial Monitor for debugging
  Serial.printf("Time: %02d:%02d\n", currentHour, currentMinute);

  // --- DISPLAY HOURS IN BINARY ---
  for (int i = 0; i < 4; i++) {
    // Bitshift to check each bit, starting from the highest (bit 3) to lowest (bit 0)
    int bitState = (currentHour >> (3 - i)) & 1;
    digitalWrite(hourPins[i], bitState);
  }

  // --- DISPLAY MINUTES IN BINARY ---
  for (int i = 0; i < 6; i++) {
    // Bitshift from highest (bit 5) to lowest (bit 0)
    int bitState = (currentMinute >> (5 - i)) & 1;
    digitalWrite(minutePins[i], bitState);
  }

  // Update the watch display every second
  delay(1000);
}
