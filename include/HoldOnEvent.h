/*
 * HoldOnEvent.h
 *
 *  Created on: Sep 14, 2011
 *      Author: caioviel
 */

#ifndef HOLDONEVENT_H_
#define HOLDONEVENT_H_

#include <libcpputil/logger/Logger.h>
using namespace cpputil::logger;

#include "MMIEvent.h"
#include "Parsable.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

/**
 * This class represent a event for the Hold On mechanism.
 * HoldOn Events are event used to control the Hold On mechanism.
 */
class HoldOnEvent : public Parsable, public MMIEvent, public cpputil::logger::Loggable {
public:
	enum HoldOnEventType {NONE, GO_BACK};

	/**
	 * Contrutor.
	 * @param deviceId Name of the device that generate the event.
	 * @param eventType Type od the event.
	 */
	HoldOnEvent(std::string deviceId, HoldOnEventType type);

	/**
	 * Destructor
	 */
	virtual ~HoldOnEvent();

	/**
	 * This method returns the HoldOn event type.
	 * @return The HoldOn Event Type.
	 */
	HoldOnEventType getHoldOnEventType();

	/**
	 * This method returns the timestamp event type.
	 * @return a string that contains the timestamp.
	 */
	std::string getTimestamp();

	/**
	 * This method allows the setting of the event timestamp..
	 * @param timeStamp of the event
	 */
	void setTimestamp(std::string timeStamp);



private:
	/**
	 * Internal constructor used by the friends classes.
	 */
	HoldOnEvent();

	/**
	 * Translate and set a XML document in a equivalent representation of a KeyEvent in this instance.
	 * @param data The XML document representation of a KeyEvent.
	 */
	void parseXMLData(XMLData* data);

	/*
	 * This methods realize the parse of a event represented by a json string,
	 * setting up the current instance with the given information.
	 * @param jsonString A string that contains the XML Document information
	 */
	void parseJson(std::string jsonString);

private:

	HoldOnEventType type;
	std::string timestamp;

	Logger* logger;

friend class HoldOnEventFactory;
};

}
}
}
}

#endif /* HOLDONEVENT_H_ */
