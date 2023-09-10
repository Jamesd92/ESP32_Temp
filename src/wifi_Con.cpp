#include <wiFi.h>
#include "wifi_Con.h"

const char* ssid = "Turtles all the way down";
const char* password = "Whanny22";

void WIFI_Connect(){
    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
} 

String getIP() {
  IPAddress ipAddress = WiFi.localIP();
  String currentIP = ipAddress.toString(); // Convert IPAddress to String
  return currentIP;
}
