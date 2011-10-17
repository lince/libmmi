/*
 * AccelerationFactory.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/AccelerationFactory.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

AccelerationFactory::AccelerationFactory() {
	// TODO Auto-generated constructor stub

}

AccelerationFactory::~AccelerationFactory() {
	// TODO Auto-generated destructor stub
}

MMIEvent* AccelerationFactory::CreateEvent(XMLData* data) {
	AccelerationEvent* event = new AccelerationEvent();
	event->parseXMLData(data);
	return event;
}

MMIEvent* AccelerationFactory::CreateEvent(string jsonString) {
	AccelerationEvent* event = new AccelerationEvent();
	event->parseJson(jsonString);
	return event;
}

}
}
}
}
