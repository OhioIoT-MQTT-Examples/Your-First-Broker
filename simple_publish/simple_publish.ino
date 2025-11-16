

#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

WiFiClient wifi_client;
PubSubClient mqtt_client;

#define WIFI_SSID "[YOUR WIFI SSID]"
#define WIFI_PASS "[YOUR WIFI PASS]"
#define MQTT_HOST "[THE IP ADDRESS OF YOUR BROKER]"
#define MQTT_PORT 1883
#define CLIENT_ID "my_first_publisher"


#define PUB_INTERVAL 3000
unsigned long pub_timer;


void setup() {

	Serial.begin(115200);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while (WiFi.status() != WL_CONNECTED) {}
	Serial.println("connected to wifi");

	mqtt_client.setClient(wifi_client);
	mqtt_client.setServer(MQTT_HOST, MQTT_PORT);

	mqtt_client.connect(CLIENT_ID);
	if (mqtt_client.state() == 0) Serial.println("connected to mqtt");

}


void loop() {
	if (millis() - pub_timer > PUB_INTERVAL) {
		if (mqtt_client.connected()) {
			mqtt_client.publish("ping", "I'm here - I'm alive");
			Serial.println("sending my ping");
			pub_timer = millis();
		}
	}
}

