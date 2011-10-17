/*
 * EventFactory.h
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#ifndef EVENTFACTORY_H_
#define EVENTFACTORY_H_

#include "Parsable.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi{

class EventFactory {
public:
	virtual ~EventFactory() {};

	virtual MMIEvent* CreateEvent(XMLData* data) = 0;

	virtual MMIEvent* CreateEvent(string jsonString) = 0;
};

}
}
}
}


#endif /* EVENTFACTORY_H_ */
