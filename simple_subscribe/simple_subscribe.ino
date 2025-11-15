

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

WiFiClient wifi_client;
PubSubClient mqtt_client;

#define WIFI_SSID "CenturyLink0447"
#define WIFI_PASS "change_after_video"
#define MQTT_HOST "192.168.0.69"
#define MQTT_PORT 1883
#define CLIENT_ID "my_first_subscriber"


void message_handler(char* topic, byte* payload, unsigned int len) {
  Serial.print("\ttopic: ");
	Serial.print(topic);
	Serial.print("\t payload: ");
	for (int i = 0; i<len; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
}


void setup() {

	Serial.begin(115200);
	
	mqtt_client.setClient(wifi_client);
	mqtt_client.setServer(MQTT_HOST, MQTT_PORT);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED) {}
	Serial.println("connected to wifi");

	mqtt_client.connect(CLIENT_ID);

	if (mqtt_client.state() == 0) Serial.println("connected to mqtt");

	mqtt_client.setCallback(message_handler);
	mqtt_client.subscribe("ping");
}


void loop() {
	mqtt_client.loop();
}

