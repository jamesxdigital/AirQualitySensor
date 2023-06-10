// Include necessary libraries
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <GP2Y1010_DustSensor.h>

// WiFi network credentials
#define WLAN_SSID "JamesiPhone"
#define WLAN_PASS "jeffthedog"

// Adafruit.io MQTT setup credentials
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883 // use 8883 for SSL
#define AIO_USERNAME "jmtln"
#define AIO_KEY "2c981ece5d9e468881829c7fd6ada375"

// Define the time to sleep (in seconds) before the ESP32 wakes up
#define TIME_TO_SLEEP 5

// Initialize a counter to keep track of the number of boots
RTC_DATA_ATTR int bootCount = 0;

// Create an ESP8266 WiFiClient to connect to the MQTT server.
WiFiClient client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup feeds called 'dustsensorFeed' and 'gassensor' for publishing
Adafruit_MQTT_Publish dustsensorFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/dustsensor");
Adafruit_MQTT_Publish gassensor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/gassensor");

// Dust sensor setup
const int dust_sensor_led_pin = 21;
const int dust_sensor_analog_pin = A3;
GP2Y1010_DustSensor dustsensor;

// Gas sensor setup
int sensorA4Value;

void setup()
{
  Serial.begin(115200);
  // Initialize dust sensor
  dustsensor.begin(dust_sensor_led_pin, dust_sensor_analog_pin);
  // Read gas sensor value
  sensorA4Value = analogRead(A4);
  // Get dust density
  float dust = dustsensor.getDustDensity();
  pinMode(A4, INPUT); // set gas sensor pin to receive input
  delay(10);

  Serial.println(F("IoT - Air Quality Monitor - James Milton"));

  // Connect to WiFi network
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Connect to Adafruit.io MQTT server
  MQTT_connect();

  // Publish sensor values to the respective feeds
  dustsensorFeed.publish(dust);
  gassensor.publish(sensorA4Value);

  // Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  // Print the wakeup reason for ESP32
  Serial.println("Wakeup caused by timer");

  // Configure the wake up source and set time to sleep
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  Serial.println("ESP32 setup to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
  Serial.println("Going to sleep now");

  // Go to deep sleep
  esp_deep_sleep_start();
}

void loop() {} // No implementation in loop as everything is done in setup

// Function to connect and reconnect to MQTT server as necessary
void MQTT_connect()
{
  int8_t ret;

  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0)
  { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); // wait 5 seconds
  }
  Serial.println("MQTT Connected!");
}
