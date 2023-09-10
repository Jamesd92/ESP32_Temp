# ESP32_Temp
ESP32 with Temperature and MQTT 

This is using PlatformIO 

[env:nodemcu-32s]
platform = espressif32
board = nodemcu-32s
framework = arduino
monitor_speed = 115200
lib_deps = 
	adafruit/DHT sensor library@^1.4.4
	olikraus/U8g2@^2.35.4
	adafruit/Adafruit GFX Library@^1.11.7
	adafruit/Adafruit SSD1306@^2.5.7
	knolleary/PubSubClient@^2.8

The main functionality is to Read a DHT22 and write the data to InfluxDB. This is done via MQTT and nodeRed
