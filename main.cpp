// Do not remove the include below
#include "main.h"
#include "HomeGateway.h"
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

void onMessageCallBack(char* topic, byte* payload, unsigned int length);

static byte MESSAGE_BROKER_IP[] = { 192, 168, 1, 100 };
static int MESSAGE_BROKER_PORT = 1883;

EthernetClient ethClient;
PubSubClient client(MESSAGE_BROKER_IP, MESSAGE_BROKER_PORT, onMessageCallBack,
		ethClient);

HomeGateway* homeGateway = 0;

void setup() {

	homeGateway = new HomeGateway(client);

}

void loop() {

	homeGateway->onLoop();
}
void onMessageCallBack(char* topic, byte* payload, unsigned int length) {
	homeGateway->handleMessage(topic,payload,length);
}
