/*
 * XmlEvent.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <string>

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <libcpputil/logger/Logger.h>

#include "EventFactory.h"
#include "MMIEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

class EventParser : public cpputil::logger::Loggable {
public:
	static EventParser* getInstance();

	MMIEvent* ParseXMLEvent(XMLData* data);

private:
	EventParser();

	virtual ~EventParser();

	EventFactory* getFactoryByType(string type);

	void parseHead(XMLData* data);

private:
	static EventParser* _instance;
};

}
}
}
}

#endif /* EVENTPARSER_H */
