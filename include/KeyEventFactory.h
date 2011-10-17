/*
 * ButtonEvent.h
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#ifndef KEYEVENTFACTORY_H_
#define KEYEVENTFACTORY_H_

#include "EventFactory.h"
#include "KeyEvent.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

class KeyEventFactory : public EventFactory {
public:
	KeyEventFactory();

	virtual ~KeyEventFactory();

	virtual MMIEvent* CreateEvent(XMLData* data);

	virtual MMIEvent* CreateEvent(string jsonString);

private:

	string buttonId;
};

}
}
}
}

#endif /* BUTTONEVENT_H_ */
