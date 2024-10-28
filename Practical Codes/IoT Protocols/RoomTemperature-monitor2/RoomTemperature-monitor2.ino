/*
* TEMPERATURE&HUMIDITY MONITORING------------------
*  # Devices:
*     -> DHT22 sensor
*     -> ESP32
*  # Technologies:
*     -> Protocol: MQTT
*     -> Broker: Mosquitto (test.mosquitto.org)
*  # Activity(Non-encrypted Data Transmission):
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to the platform (Mosquitto) via MQTT broker
*
*   ANGAZA ELIMU&ALX - IOT SCHOOL: Cohort 1, 2024
* --------------------------------------------------
*/

/*
 Support libraries -------------------------------------------------------------
*/
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
//#include "secrets.h"      // For connection authentication credentials
// -----------------------------------------------------------------------------

/*
 Control Variables -------------------------------------------------------------
*/
//---- DHT settings
#define DHTPIN 7            // Pin where DHT22 is connected
#define DHTTYPE DHT22       // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

//---- Onboard LED
#define ONBOARD_LED_PIN 13   // Used as a signal LED for WiFi connection

/*
 Connection credentials -------------------------------------------------------------
*/
//---- WiFi settings
const char* ssid     = "";
const char* password = "";

//---- MQTT Broker settings
const char* mqtt_server = "test.mosquitto.org"; // MQTT broker - Mosquitto
const int mqtt_port = 1883;                     // Non-encrypted port (default for MQTT)

//---- MQTT Pub/Sub Control topics
String dht_temp_topic = "dht22/temperature";
String dht_humid_topic = "dht22/humidity";

//---- Setup connection client
WiFiClient espClient;
PubSubClient client(espClient);

//---- Setup message handlers
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
// -----------------------------------------------------------------------------

/*
 Control Functions -------------------------------------------------------------
*/
//---- Callback handler for MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  String incomingMessage = "";
  for (int i = 0; i < length; i++) incomingMessage += (char)payload[i];
  Serial.println("Message arrived [" + String(topic) + "]: " + incomingMessage);
}

//---- Initiate MQTT reconnection
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";   // Create a random client ID
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      // Subscribe to the desired topic
      client.subscribe(dht_temp_topic.c_str());
      client.subscribe(dht_humid_topic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

//---- Initialize main instances execution
void setup() {
  Serial.begin(115200);
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  //---- Initialize WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //---- Initialize signal LED mode
  pinMode(ONBOARD_LED_PIN, OUTPUT);
  digitalWrite(ONBOARD_LED_PIN, HIGH);      // Turn ON onboard LED

  //---- Initialize WiFi connection loader and signal LED
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(250);
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(250);
  }

  Serial.println("\nWiFi connected\nIP address: ");
  Serial.println(WiFi.localIP());           //---- Print WiFi IP address

  //---- Turn OFF signal LED on WiFi connection
  digitalWrite(ONBOARD_LED_PIN, LOW);

  //---- Configure MQTT server and set the callback function
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //---- Initialize DHT sensor
  dht.begin();
}

//---- Ensures iterative execution of main control instances
void loop() {
  //---- Initiate MQTT broker reconnection if connection fails
  if (!client.connected()) reconnect();
  client.loop();                                // Ensure constant processing of MQTT client

  //---- Read DHT22 sensor parameters
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();

  //---- Check failed sensor reading
  if (isnan(temp) || isnan(humid)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("\nTemperature: " + String(temp) + "\nHumidity: " + String(humid));

  //---- Publish temperature & humidity data to the MQTT topic
  publishMessage(dht_temp_topic.c_str(), String(temp), true);
  publishMessage(dht_humid_topic.c_str(), String(humid), true);

  //---- Delays iterative execution to every 1 min
  delay(10000 ); // Changed to 60 seconds
}

//---- MQTT broker messages publishing handler
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), retained)) {
    Serial.println("Message published [" + String(topic) + "]: " + payload);
  } else {
    Serial.println("Failed to publish message");
  }
}
