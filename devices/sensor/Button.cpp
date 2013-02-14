/*
 * Button.cpp
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#include "Button.h"

Button::Button(int sensorID, int port, IEventHandler* eventHandler) :
		Sensor(sensorID,eventHandler) {
	digitalPort = port;

}

Button::~Button() {
}

int Button::readValue() {
	int value = digitalRead(digitalPort);
	return value;
}
