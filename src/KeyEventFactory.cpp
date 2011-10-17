/*
 * AccelerationFactory.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/KeyEventFactory.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

KeyEventFactory::KeyEventFactory() {
	// TODO Auto-generated constructor stub

}

KeyEventFactory::~KeyEventFactory() {
	// TODO Auto-generated destructor stub
}

MMIEvent* KeyEventFactory::CreateEvent(XMLData* data) {
	KeyEvent* event = new KeyEvent();
	event->parseXMLData(data);
	return event;
}

MMIEvent* KeyEventFactory::CreateEvent(string jsonString) {
	KeyEvent* event = new KeyEvent();
	event->parseJson(jsonString);
	return event;
}

}
}
}
}
