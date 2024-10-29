/*
* TEMPERATURE&HUMIDITY MONITORING------------------
*  # Devices:
*     -> DHT22 sensor
*     -> ESP32
*  # Technologies:
*     -> Protocol: MQTT
*     -> Broker: HiveMQ(https://console.hivemq.cloud)
*  # Activity:
*    >> Node 1
*    >> Topology: Meshed Network Topology by Mesh Library
*    -> Measure room temperature and humidity values
*    -> Send the recorded data to Node 2 connected to it via mesh
*
*   ANGAZA ELIMU&ALX - IOT SCHOOL: Cohort 1, 2024
* --------------------------------------------------
*/

/*
 Support libraries -------------------------------------------------------------
*/
#include <painlessMesh.h>
#include <DHT.h>

#define MESH_PREFIX "ESP32Mesh1"
#define MESH_PASSWORD "MeshNode1"
#define MESH_PORT 5555
// -----------------------------------------------------------------------------

/*
 Control Variables -------------------------------------------------------------
*/
// DHT22 setup
#define DHTPIN 7          // GPIO where DHT22 is connected
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

Scheduler userScheduler;
painlessMesh mesh;
// -----------------------------------------------------------------------------

/*
 Control Functions -------------------------------------------------------------
*/
//---- Initialize messages handler
void sendMessage(); // Forward declaration
Task taskSendMessage(TASK_SECOND * 10, TASK_FOREVER, &sendMessage);  // Fanout message every 10 seconds

//---- Initialize main instances execution
void setup() {
  Serial.begin(115200);
  dht.begin();

  // Mesh network configuration
  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION); // Optional: DEBUGGING
  mesh.init(MESH_PREFIX, MESH_PASSWORD, MESH_PORT);
  mesh.onReceive(&receivedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

//---- Synchronously update mesh operation
void loop() {
  mesh.update();
}

// Message fanout handler
void sendMessage() {
  //---- Read DHT22 sensor parameters
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  //---- Check failed sensor reading
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //---- Package sensor data and broadcast to mesh network
  String msg = String(temperature) + "," + String(humidity);
  mesh.sendBroadcast(msg);
  Serial.println("Sent data: " + msg);
}

// Callback handler
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}
