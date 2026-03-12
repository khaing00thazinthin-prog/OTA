#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

#define FW_VERSION "1.0.1"  // Current firmware version
const int ledPin = 2;
// Replace with your Wi-Fi credentials
const char* ssid = "BabyAncestoriNteli";
const char* password = "bb2020$!@@";

// URL to the latest firmware binary on GitHub
// Make sure this points directly to the raw .bin file
#define UPDATE_URL "https://github.com/khaing00thazinthin-prog/OTA/raw/refs/heads/main/firmware.bin"
WiFiClient client;
void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(ledPin, OUTPUT);
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFailed to connect to Wi-Fi");
    return;
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Check for firmware update
  checkForUpdate();
  Serial.println("Firmware Version: 1.0.1");
}

void loop() {
  // You can periodically call update check here
  // For demo, we only check once in setup

  digitalWrite(ledPin, LOW);   // LED ON
  delay(2000);

  digitalWrite(ledPin, HIGH);  // LED OFF
  delay(2000);
}

void checkForUpdate() {
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, UPDATE_URL);

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Update failed. Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No update available.");
      break;

    case HTTP_UPDATE_OK:
      Serial.println("Update successful! ESP will restart automatically.");
      break;
  }
}
