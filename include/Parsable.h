/*
 * XmlEvent.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef XMLEVENT_H_
#define XMLEVENT_H_

#include <string>

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include "MMIEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

/**
 * This structure contains the data used by the parsers during the XML parser process.
 */
typedef struct {
	/**
	 * The XML Document data payload.
	 */
	char* payload;

	/**
	 * The size of the XML Document in characters count.
	 */
	int length;

	/**
	 * The event of the id represented by the XML Document, if any.
	 */
	std::string eventId;

	/**
	 * The device id that generate the XMLDocument.
	 */
	std::string deviceId;

	/**
	 * The model of the device that generate the XML Document.
	 */
	std::string deviceModel;

	/**
	 * The type of event represented by the XML Document.
	 */
	std::string eventType;

	/**
	 * A pointer to the DOMElement that represents the XML Document.
	 */
	DOMElement* element;
} XMLData;

class Parsable {
public:
	/**
	 * Destructor
	 */
	virtual ~Parsable() {};

	/**
	 * This methods realize the parse of a event represented by a XML Document,
	 * setting up the current instance with the given information.
	 * @param data A instance of XMLData that contains the XML Document information.
	 */
	virtual void parseXMLData(XMLData* data) = 0;

	/**
	 * This methods realize the parse of a event represented by a json string,
	 * setting up the current instance with the given information.
	 * @param jsonString A string that contains the XML Document information
	 */
	virtual void parseJson(std::string jsonString) = 0;

	/**
	 * Generic Contructor.
	 */
	Parsable() {}
};

}
}
}
}

#endif /* XMLEVENT_H_ */
