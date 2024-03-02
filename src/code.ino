// code.ino
#ifndef CODE_INO
#define CODE_INO

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

const char* ssid = "UNIFI_IDO2";
const char* password = "99Bidules!";
const char* serverAddress = "http://192.168.1.252:8080/data";

// Variable statique pour stocker l'ID
static int currentID = 8214;

void connectToWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void sendDataToServer(int value) {
    Serial.println("Sending data to server...");
    WiFiClient client;
    HTTPClient http;

    // Obtenez l'adresse IP locale du microcontrôleur
    String localIP = WiFi.localIP().toString();

    // Incrémente l'ID
    currentID++;

    // Construire l'objet JSON(adaptable pour charque microcontroleur)
    DynamicJsonDocument jsonDocument(1024); // Taille du document JSON, ajustez si nécessaire
    jsonDocument["ID"] = currentID;
    jsonDocument["Type de Mesure"] = "Temperature";
    jsonDocument["Valeur"] = value;
    jsonDocument["Nom Objet"] = "esp32(1)";
    jsonDocument["Adresse IP"] = localIP;

    // Sérialiser l'objet JSON en chaîne
    String jsonData;
    serializeJson(jsonDocument, jsonData);

    http.begin(client, serverAddress);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
        Serial.print("Server response: ");
        Serial.println(http.getString());
    } else {
        Serial.print("HTTP error: ");
        Serial.println(httpResponseCode);
    }

    http.end();
}

#endif  // CODE_INO