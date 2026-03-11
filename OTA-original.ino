#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClientSecure.h>
// -------- CONFIG --------
#define LED_PIN LED_BUILTIN

#define FW_VERSION "1.0.0"  // Current firmware version
#define UPDATE_URL "https://github.com/khaing00thazinthin-prog/OTA/releases/download/V1.0.0/firmware.bin"
const char* ssid = "BabyAncestoriNteli";         // Your Wi-Fi SSID
const char* password = "bb2020$!@@"; // Your Wi-Fi password
// -----------------------

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    retry++;
    if (retry > 60) {   // Wait max 30 seconds
      Serial.println("\nFailed to connect to Wi-Fi. Restarting...");
      ESP.restart();
    }
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());

  // -------- Remote OTA Update --------
   WiFiClientSecure client;
  client.setInsecure();
  Serial.println("Checking for firmware update...");
  t_httpUpdate_return ret = ESPhttpUpdate.update(client,UPDATE_URL);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Update failed. Error (%d): %s\n", 
                    ESPhttpUpdate.getLastError(), 
                    ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No new updates available.");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("Update success! Rebooting...");
      break;
  }
}

void loop() {
  // Your main code here
  // Example: Blink LED
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
}
