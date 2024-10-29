/*
* TEMPERATURE&HUMIDITY MONITORING------------------
*  # Devices:
*     -> DHT22 sensor
*     -> ESP32
*  # Technologies:
*     -> Protocol: MQTT
*     -> Broker: HiveMQ(https://console.hivemq.cloud)
*  # Activity(Meshed Network Topology by Serial):
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to the platform(HiveMQ) via MQTT broker
*
*   ANGAZA ELIMU&ALX - IOT SCHOOL: Cohort 1, 2024
* --------------------------------------------------
*/

/*
 Support libraries -------------------------------------------------------------
*/
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "secrets.h"      // For connection authentication credentials
// -----------------------------------------------------------------------------

/*
 Control Variables -------------------------------------------------------------
*/
//---- Onboard LED
#define ONBOARD_LED_PIN 13   // Used as a signal LED for wifi connection

//---- Setup connection client
WiFiClientSecure espClient;
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
    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");

      // Subscribe to the desired topic
      client.subscribe(mqtt_topic);
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
  Serial1.begin(9600);    // Serial1 for receiving data from Node 2

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

  //---- Initialize secure connection to broker
  espClient.setCACert(root_ca);              // Set the root certificate
  client.setServer(mqtt_server, mqtt_port);  // Configure MQTT server
  client.setCallback(callback);              // Set the callback function for MQTT messages

}

//---- Ensures iterative execution of main control instances
void loop() {
  //---- Initiate MQTT broker reconnection if connection fails
  if (!client.connected()) reconnect();
  client.loop();                                // Ensure constant processing of MQTT client

  // Check if data is available on Serial1
  if (Serial1.available() > 0) {
    String data = Serial1.readStringUntil('\n');
    Serial.println("Received data: " + data);  // Debugging

    //---- Publish temperature & humidity data to the MQTT topic
    publishMessage(mqtt_topic, data.c_str(), true);
  }

  //---- Delays iterative execution to every 1min
  delay(10000);
}

//---- MQTT broker messages publishing handler
void publishMessage(const char* topic, String payload, boolean retained) {
  if (client.publish(topic, payload.c_str(), retained)) {
    Serial.println("Message published [" + String(topic) + "]: " + payload);
  } else {
    Serial.println("Failed to publish message");
  }
}
