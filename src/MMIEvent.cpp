/*
 * MMIEvent.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#include "../include/MMIEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

MMIEvent::MMIEvent(string deviceId, string eventType) {
	this->deviceId = deviceId;
	this->eventType = eventType;
}

MMIEvent::~MMIEvent() {

}

string MMIEvent::getDeviceId() {
	return deviceId;
}

string MMIEvent::getEventType() {
	return eventType;
}

}
}
}
}
