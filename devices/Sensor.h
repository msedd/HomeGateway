/*
 * Sensor.h
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "IEventHandler.h"
#include "devices/Device.h"

class Sensor : public Device {
public:
	Sensor(int, IEventHandler*);
	virtual ~Sensor();
	void readAndDispatch();


protected:
	virtual int readValue()=0;

private:

	bool hasChanged();
	void sendEvent(int);
	int lastValue;
	IEventHandler* eventHandler;
};

#endif /* SENSOR_H_ */
