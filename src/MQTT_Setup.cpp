#include "MQTT_Setup.h"

const char* mqttServer = "192.168.1.114";
const int mqttPort = 1883;  // Default MQTT port

void MQTT_Initialize() {
  MQTTclient.setServer(mqttServer, mqttPort);
}

bool MQTT_Connect() {
  while (!MQTTclient.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (MQTTclient.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      return true;
    } else {
      Serial.print("Failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" Retrying in 5 seconds");
      delay(5000);
    }
  }
  return false;
}

void MQTT_Post(PubSubClient& client, const char* topic, float value) {
    if (!client.connected()) {
        // Handle MQTT reconnection if necessary
        // You can add code to reconnect to the MQTT broker here
    }

    // Convert the float value to a string
    char msg[15];  // Adjust buffer size as needed
    dtostrf(value, 8, 2, msg);  // Convert float to string

    // Publish the message to the specified MQTT topic
    client.publish(topic, msg);
}