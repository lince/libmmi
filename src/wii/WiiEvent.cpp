/*
 * WiiInputEvent.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#include "../../include/wii/WiiEvent.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiEvent::WiiEvent(string deviceId, MoveAction moveType) :
		MMIEvent(deviceId, "wiiEvent") {

	this->moveType = moveType;
}

WiiEvent::~WiiEvent() {

}

MoveAction WiiEvent::getMoveAction() {
	return moveType;
}


}
}
}
}
}
