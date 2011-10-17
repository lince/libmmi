/*
 * XmlEvent.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef EVENTPARSER_H
#define EVENTPARSER_H

#include <string>
using namespace std;

#include <xercesc/dom/DOM.hpp>
XERCES_CPP_NAMESPACE_USE

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include "EventFactory.h"
#include "MMIEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

class EventParser : public Loggable {
public:
	static EventParser* getInstance();

	MMIEvent* ParseXMLEvent(XMLData* data);

private:
	EventParser();

	~EventParser();

	EventFactory* getFactoryByType(string type);

	void parseHead(XMLData* data);

private:
	static EventParser* _instance;

	Logger* logger;
};

}
}
}
}

#endif /* EVENTPARSER_H */
