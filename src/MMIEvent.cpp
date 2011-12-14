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

MMIEvent::MMIEvent(std::string deviceId, std::string eventType) {
	this->deviceId = deviceId;
	this->eventType = eventType;
}

MMIEvent::~MMIEvent() {

}

std::string MMIEvent::getDeviceId() {
	return deviceId;
}

std::string MMIEvent::getEventType() {
	return eventType;
}

}
}
}
}
