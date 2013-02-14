/*
 * Sensor.h
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Arduino.h"
#include "IEventHandler.h"

class Sensor {
public:
	Sensor(int, IEventHandler*);
	virtual ~Sensor();
	void readAndDispatch();
	int getSensorID();

protected:
	virtual int readValue()=0;

private:

	bool hasChanged();
	void sendEvent(int);
	int lastValue;
	int id;
	IEventHandler* eventHandler;
};

#endif /* SENSOR_H_ */
