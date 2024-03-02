#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include "code.ino"

void setup() {
    Serial.begin(115200);
    connectToWiFi();
    configTime(0, 0, "pool.ntp.org");
}

void loop() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    char timeString[20];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", &timeinfo);
    Serial.println(timeString);

    int value = 32;  // Votre logique pour lire la valeur du capteur
    Serial.println(value, DEC);

    // Envoyer les données au serveur
    sendDataToServer(value);

    delay(5000);
}