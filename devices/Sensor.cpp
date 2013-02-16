/*
 * Sensor.cpp
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#include "Sensor.h"

Sensor::Sensor(int sensorID, IEventHandler* aEventHandler) :
		Device(sensorID) {
	lastValue = 0;
	eventHandler = aEventHandler;
}

Sensor::~Sensor() {
}
void Sensor::readAndDispatch() {
	if (hasChanged()) {
		sendEvent(readValue());
	}

}

bool Sensor::hasChanged() {
	int v = readValue();
	if (v != lastValue) {
		lastValue = v;
		return true;
	}
	return false;
}
void Sensor::sendEvent(int value) {
	char buffer[10];
	sprintf(buffer, "[%d,%d]", getID(), value);
	eventHandler->handleEvent(getID(), value);
}
