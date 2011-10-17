/*
 * MMIEvent.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef MMIEVENT_H_
#define MMIEVENT_H_

#include <iostream>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

/**
 * This class represent a generic Multimodal Event.
 * All multimodal event types must implement a specialization of this class.
 */
class MMIEvent {
public:

	/**
	 * Contrutor.
	 * @param deviceId Name of the device that generate the event.
	 * @param eventType Type od the event.
	 */
	MMIEvent(string deviceId, string eventType);

	/**
	 * Destructor
	 */
	virtual ~MMIEvent();

	/**
	 * This method returns the id of the device that generate the event.
	 * @return Device id.
	 */
	string getDeviceId();

	/**
	 * This method returns the type of event.
	 * @return Event type.
	 */
	string getEventType();

protected:
	string deviceId;
	string eventType;
};

}
}
}
}

#endif /* MMIEVENT_H_ */
