#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Sumit's Galaxy S23";
const char* password = "Sumit_07";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;

const char* publish_topic = "ldr/light_state";
const char* subscribe_topic = "led/control";

#define LDR_PIN D2  // Changed to D2
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
unsigned long lastMsg = 0;
const unsigned long interval = 2000;

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);
  if (message == "1") {
    digitalWrite(BUILTIN_LED, LOW);
    Serial.println("LED turned ON");
  } else if (message == "0") {
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.println("LED turned OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(subscribe_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  digitalWrite(BUILTIN_LED, HIGH); // LED OFF
  Serial.begin(9600);
  setup_wifi();
  delay(1000);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.setKeepAlive(60);
  client.setSocketTimeout(60);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg >= interval) {
    lastMsg = now;
    int lightState = digitalRead(LDR_PIN);
    String lightMessage = lightState == LOW ? "Dim" : "Bright";  // Adjust logic if needed
    Serial.print("LDR State (0=LOW, 1=HIGH): ");
    Serial.print(lightState);
    Serial.print(" | Light Intensity: ");
    Serial.println(lightMessage);
    lightMessage.toCharArray(msg, MSG_BUFFER_SIZE);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(publish_topic, msg);
  }
}