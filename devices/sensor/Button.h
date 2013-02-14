/*
 * Button.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "devices/Sensor.h"

class Button : public Sensor {
public:
	Button(int, int, IEventHandler*);
	virtual ~Button();
protected:
	virtual int readValue();
private:
	int digitalPort;
};

#endif /* BUTTON_H_ */
