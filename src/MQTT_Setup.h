#ifndef MQTT_Setup_H
#define MQTT_Setup_H

#include <PubSubClient.h>
#include <WiFi.h>

extern WiFiClient espClient;
extern PubSubClient MQTTclient;

void MQTT_Initialize();
bool MQTT_Connect();
void MQTT_Post(PubSubClient& client, const char* topic, float value);

#endif
