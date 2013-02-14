/*
 * IEventHandler.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef IEVENTHANDLER_H_
#define IEVENTHANDLER_H_

class IEventHandler {
public:
	virtual ~IEventHandler(){};
	virtual void handleEvent(int deviceID, int value)=0;
};

#endif /* IEVENTHANDLER_H_ */
