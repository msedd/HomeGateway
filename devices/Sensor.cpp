/*
 * Sensor.cpp
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#include "Sensor.h"

Sensor::Sensor(int sensorID, IEventHandler* aEventHandler) {
	lastValue = 0;
	id = sensorID;
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
	if (readValue() != lastValue) {
		return true;
	}
	return false;
}
void Sensor::sendEvent(int value) {
	char buffer[10];
	sprintf(buffer, "[%d,%d]", id, value);
	eventHandler->handleEvent(id,value);
}
int Sensor::getSensorID() {
	return id;
}
