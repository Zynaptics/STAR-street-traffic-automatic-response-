#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "your wifi name";
const char* password = "your wifi password";

// MQTT Broker settings
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_user = "";   // Optional, can be ""
const char* mqtt_password = ""; // Optional, can be ""

WiFiClient espClient;
PubSubClient client(espClient);

// LDR analog input pin
const int ldrPin = 35;  // Make sure this pin supports ADC

unsigned long lastMsg = 0;
const long interval = 5000; // publish every 5 seconds

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println("Starting LDR + MQTT example");

  // Connect to Wi-Fi
  setup_wifi();

  // Setup MQTT server and callback
  client.setServer(mqtt_server, mqtt_port);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int wifi_attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    wifi_attempts++;
    if (wifi_attempts > 20) {
      Serial.println("\nFailed to connect to WiFi");
      // Optionally: restart or continue trying
      return;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement or subscribe
      // client.subscribe("your_topic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    int ldrValue = analogRead(ldrPin);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Convert integer to string
    char ldrStr[10];
    sprintf(ldrStr, "%d", ldrValue);

    // Publish LDR value to MQTT topic "sensor/ldr"
    if (client.publish("sensor/ldr", ldrStr)) {
      Serial.println("MQTT publish success");
    } else {
      Serial.println("MQTT publish failed");
    }
  }
}


