/*
 * ButtonEvent.h
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#ifndef KEYEVENT_H_
#define KEYEVENT_H_

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include "MMIEvent.h"
#include "Parsable.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

/**
 * This class represent a event of type key.
 * Key Events are event generate when the user press a virtual or physical key or button.
 */
class KeyEvent : public Parsable, public MMIEvent, public Loggable {
public:

	/**
	 * Contrutor.
	 * @param deviceId Name of the device that generate the event.
	 * @param eventType Type od the event.
	 */
	KeyEvent(string deviceId, string buttonId);

	/**
	 * Destructor
	 */
	virtual ~KeyEvent();

	/**
	 * This method returns the identificator of the key
	 * @return The key Id.
	 */
	string getKeyId();

private:
	/**
	 * Internal constructor used by the friends classes.
	 */
	KeyEvent();

	/**
	 * Translate and set a XML document in a equivalent representation of a KeyEvent in this instance.
	 * @param data The XML document representation of a KeyEvent.
	 */
	void parseXMLData(XMLData* data);

	/**
	 * This methods realize the parse of a event represented by a json string,
	 * setting up the current instance with the given information.
	 * @param jsonString A string that contains the XML Document information
	 */
	virtual void parseJson(string jsonString);

private:
	string keyId;

	Logger* logger;

friend class KeyEventFactory;
};

}
}
}
}

#endif /* KEYEVENT_H_ */
