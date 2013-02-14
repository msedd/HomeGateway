/*
 * DeviceManager.cpp
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#include "DeviceManager.h"

DeviceManager::DeviceManager() {

}

DeviceManager::~DeviceManager() {

}
void DeviceManager::addActor(int deviceID, Actor* actor) {
	actorList.append(deviceID, actor);
}
void DeviceManager::addSensor(int deviceID, Sensor* sensor) {
	sensorList.append(deviceID, sensor);
}
void DeviceManager::onLoop() {

	int size = sensorList.getSize();

	for (int i = 0; i < size; i++) {
		Sensor* sensor = (Sensor*) sensorList.getElemet(i);
		sensor->readAndDispatch();
	}

}
