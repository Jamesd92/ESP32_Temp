#include <Arduino.h>
#include "wifi_Con.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"


#define LED 2
// DHTPIN 15 I2C
#define DHTPIN 15
//ESP 32 pinout: https://www.studiopieters.nl/esp32-pinout/

#define DHTTYPE DHT22

DHT dht(DHTPIN,DHTTYPE);

void setup() {

    Serial.begin(9600);
    delay(1000);

  WIFI_Connect();
  pinMode(LED, OUTPUT);
  
  //DHT 
  Serial.println(F("DHT22 test!"));
  dht.begin();
}

void loop() {

  //variables
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  //check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)){
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  digitalWrite(LED, HIGH);  //LED PIN SET HIGH

  Serial.println("LED ON"); // LED TURN ON

  delay(1000);              // 1 SEC DELAY

  digitalWrite(LED, LOW);   //LED PIN SET LOW

  Serial.println("LED OFF"); // LED TURN OFF

  delay(1000);               // 1 SEC DELAY

  

}