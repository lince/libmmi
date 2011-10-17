/*
 * AccelerationFactory.h
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#ifndef ACCELERATIONFACTORY_H_
#define ACCELERATIONFACTORY_H_

#include "EventFactory.h"
#include "AccelerationEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

class AccelerationFactory : public EventFactory {
public:
	AccelerationFactory();
	virtual ~AccelerationFactory();

	virtual MMIEvent* CreateEvent(XMLData* data);

	virtual MMIEvent* CreateEvent(string jsonString);
};

#endif /* ACCELERATIONFACTORY_H_ */

}
}
}
}
