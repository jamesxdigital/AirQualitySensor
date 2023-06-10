// AirQualitySensor.h

#ifndef LAB_13_H 
#define LAB_13_H

/****************************************************/
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <GP2Y1010_DustSensor.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "JamesiPhone"
#define WLAN_PASS       "jeffthedog"

/************************* Adafruit.io Setup *********************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "jmtln"
#define AIO_KEY         "2c981ece5d9e468881829c7fd6ada375"

/******************* Sleep and Timed Wakeup Setup ****************************/
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  5        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

/****************************** Global State  ********************************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
// Setup a feeds called 'dustsensorFeed' and 'gassensor' for publishing
Adafruit_MQTT_Publish dustsensorFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dustsensor");
Adafruit_MQTT_Publish gassensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gassensor");

/*************************** Sensor Setup ************************************/
//dust sensor setup
const int dust_sensor_led_pin = 21;
const int dust_sensor_analog_pin = A3;
GP2Y1010_DustSensor dustsensor;
//gas sensor setup
int sensorA4Value;


#endif
