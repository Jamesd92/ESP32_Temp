#include <Arduino.h>
#include "wifi_Con.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

// MQTT
#include <PubSubClient.h>
#include <MQTT_Setup.h>
WiFiClient espClient;
PubSubClient MQTTclient(espClient);
//DHT
#include "Adafruit_Sensor.h"
#include "DHT.h"

//DHT Setup
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN,DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printTemp(float,float,float,String);

void setup() {
  Serial.begin(115200);
  delay(5000);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Connecting to Wifi"));
  WIFI_Connect();
  Serial.println(F("Starting MQTT connestion"));
  // Initialize MQTT client
  MQTT_Initialize();
  Serial.println(F("DHT22 Boot!"));
  dht.begin();
}


void loop() {

    //variables
  String ip;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  ip = getIP();

//--------------------- MQTT Logic-------
  if (!MQTTclient.connected()) {
    MQTT_Connect();
  }

  MQTTclient.loop();
 

  if (isnan(h) || isnan(t) || isnan(f)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } else{
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  delay(2000);
  printTemp(t,h,hic,ip);
  } 


}
void printTemp(float i,float j,float k,String ip){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Temp:");
    display.print(i);
    MQTT_Post(MQTTclient, "ESP32/Temperature", i);
    display.println(" C");
    display.print("Hum:");
    display.print(j);
    MQTT_Post(MQTTclient, "ESP32/Humidity",j);
    display.println("%");
    display.print("Feels: ");
    display.print(k);
    MQTT_Post(MQTTclient, "ESP32/Relative", k);
    display.println("C");
    display.print(ip);

    // Display the updated content
    display.display();
}