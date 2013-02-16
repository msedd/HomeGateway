/*
 * HomeGateway.h
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#ifndef HOMEGATEWAY_H_
#define HOMEGATEWAY_H_

#include <Ethernet.h>
#include <PubSubClient.h>
#include "devices/DeviceManager.h"
#include "devices/IEventHandler.h"

class HomeGateway: public IEventHandler {
public:
	HomeGateway(PubSubClient&);
	virtual ~HomeGateway();
	virtual void handleEvent(int deviceID, int value);
	void handleMessage(char* topic, byte* payload, unsigned int length);
	void onLoop();

private:
	void connect();
	PubSubClient& client;
	DeviceManager* deviceManager;
	enum {
		DEVICEID_LED1 = 1,
		DEVICEID_LED2 = 2,
		DEVICEID_LED3 = 3,
		DEVICEID_LED4 = 4,
		DEVICEID_TASTER1 = 5,
		DEVICEID_TASTER2 = 6
	};
	enum {
		DIGITAL_IO0 = 0,
		DIGITAL_IO1 = 1,
		DIGITAL_IO2 = 2,
		DIGITAL_IO3 = 3,
		DIGITAL_IO4 = 4,
		DIGITAL_IO5 = 5,
		DIGITAL_IO6 = 6,
		DIGITAL_IO7 = 7,
		DIGITAL_IO8 = 8,
		DIGITAL_IO9 = 9,
		DIGITAL_IO10 = 10,
		DIGITAL_IO11 = 11,
		DIGITAL_IO12 = 12,
		DIGITAL_IO13 = 13
	};

	static byte MAC[];

	static char* MESSAGING_TOPIC_IN;
	static char* MESSAGING_TOPIC_OUT;
	static char* MESSAGING_CLIENT_ID;

};

#endif /* HOMEGATEWAY_H_ */
