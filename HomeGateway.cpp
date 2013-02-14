/*
 * HomeGateway.cpp
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#include "HomeGateway.h"
#include "devices/sensor/Button.h"
#include "HardwareSerial.h"

byte HomeGateway::MESSAGE_BROKER_IP[] = { 192, 168, 1, 100 };
byte HomeGateway::MAC[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char* HomeGateway::MESSAGING_TOPIC_IN = "sensor-topic-in";
char* HomeGateway::MESSAGING_TOPIC_OUT = "actor-topic-out";
char* HomeGateway::MESSAGING_CLIENT_ID = "Arduino Home Gateway";

HomeGateway::HomeGateway() {

	client = new PubSubClient(MESSAGE_BROKER_IP, MESSAGE_BROKER_PORT, 0,
			ethClient);

	deviceManager = new DeviceManager();
	Button* taster1 = new Button(DEVICEID_TASTER1, DIGITAL_IO6, this);
	Button* taster2 = new Button(DEVICEID_TASTER2, DIGITAL_IO7, this);

	deviceManager->addSensor(taster1->getSensorID(), taster1);
	deviceManager->addSensor(taster2->getSensorID(), taster2);

	Serial.begin(9600);
	Serial.println("Arduino HomeGateway 0.1 try to connect to MQTT Server");
	connect();
}

HomeGateway::~HomeGateway() {

	delete client;
}

void HomeGateway::onLoop() {

	client->loop();
	deviceManager->onLoop();

}
void HomeGateway::handleEvent(int sensorID, int value) {
	char buffer[10];
	sprintf(buffer, "[%d,%d]", sensorID, value);

	client->publish(MESSAGING_TOPIC_OUT, buffer);
}

void HomeGateway::connect() {

	Ethernet.begin(MAC);
	int connRC = client->connect(MESSAGING_CLIENT_ID);

	if (!connRC) {
		Serial.println(connRC);
		Serial.println("Could not connect to MQTT Server");
		Serial.println("Please reset the arduino to try again");

		delay(100);
		exit(-1);
	} else {
		Serial.println("Connected to MQTT Server...");
		client->subscribe(MESSAGING_TOPIC_OUT);

	}
}
