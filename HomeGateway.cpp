/*
 * HomeGateway.cpp
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#include "HomeGateway.h"
#include "devices/sensor/Button.h"
#include "devices/actor/LED.h"
#include "HardwareSerial.h"

byte HomeGateway::MAC[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char* HomeGateway::MESSAGING_TOPIC_IN = "sensor-topic-in";
char* HomeGateway::MESSAGING_TOPIC_OUT = "actor-topic-out";
char* HomeGateway::MESSAGING_CLIENT_ID = "Arduino Home Gateway";

HomeGateway::HomeGateway(PubSubClient& pubSubClient) :
		client(pubSubClient) {

	deviceManager = new DeviceManager();
	Button* taster1 = new Button(DEVICEID_TASTER1, DIGITAL_IO6, this);
	Button* taster2 = new Button(DEVICEID_TASTER2, DIGITAL_IO7, this);

	LED* led1 = new LED(DEVICEID_LED1,DIGITAL_IO2);
	LED* led2 = new LED(DEVICEID_LED2,DIGITAL_IO3);
	LED* led3 = new LED(DEVICEID_LED3,DIGITAL_IO4);
	LED* led4 = new LED(DEVICEID_LED4,DIGITAL_IO5);

	deviceManager->addSensor(taster1->getID(), taster1);
	deviceManager->addSensor(taster2->getID(), taster2);

	deviceManager->addActor(led1->getID(),led1);
	deviceManager->addActor(led2->getID(),led2);
	deviceManager->addActor(led3->getID(),led3);
	deviceManager->addActor(led4->getID(),led4);


	Serial.begin(9600);
	Serial.println("Arduino HomeGateway 0.1 try to connect to MQTT Server");
	connect();
}

HomeGateway::~HomeGateway() {

}

void HomeGateway::onLoop() {

	client.loop();
	deviceManager->onLoop();

}
void HomeGateway::handleEvent(int sensorID, int value) {
	char buffer[10];
	sprintf(buffer, "[%d,%d]", sensorID, value);

	client.publish(MESSAGING_TOPIC_IN, buffer);
}
void HomeGateway::handleMessage(char* topic, byte* payload,
		unsigned int length) {

	// Allocate the correct amount of memory for the payload copy
	byte* p = (byte*) malloc(length);
	// Copy the payload to the new buffer
	memcpy(p, payload, length);
	char buffer[length + 1];
	snprintf(buffer, length + 1, "%s", p);
	free(p);

	Serial.println("empfange Nachricht:");
	Serial.println(buffer);

	Serial.println("parse Nachricht:");

	String message(buffer);
	int start = message.indexOf('[');
	int end = message.indexOf(']');
	message = message.substring(start + 1, end);
	start = message.indexOf(',');
	String strId = message.substring(0, start);
	String strValue = message.substring(start + 1, message.length());

	Serial.println("ID: " + strId);
	Serial.println("Value: " + strValue);

	int id = strId.toInt();
	int value = strValue.toInt();
	deviceManager->setValue(id,value);
}

void HomeGateway::connect() {

	Ethernet.begin(MAC);
	int connRC = client.connect(MESSAGING_CLIENT_ID);

	if (!connRC) {
		Serial.println(connRC);
		Serial.println("Could not connect to MQTT Server");
		Serial.println("Please reset the arduino to try again");

		delay(100);
		exit(-1);
	} else {
		Serial.println("Connected to MQTT Server...");
		client.subscribe(MESSAGING_TOPIC_OUT);

	}
}
