/*
 * WiiInputEvent.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef WIIINPUTEVENT_H_
#define WIIINPUTEVENT_H_

#include "../MMIEvent.h"
using namespace ::br::ufscar::lince::mmi;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

/**
 * This enumeration represents the possibles moves that the WiiDriver can recognize.
 */
enum MoveAction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

/**
 * This class represents a interaction realized with the WiiMote.
 */
class WiiEvent : public MMIEvent {
public:
	/**
	 * Construtor
	 * @param deviceId The id of the WiiMote that generate the event
	 * @param moveType A representation of the movement recognized by the WiiDriver,
	 */
	WiiEvent(string deviceId, MoveAction moveType);

	/**
	 * Destructor
	 */
	virtual ~WiiEvent();

	/**
	 * This methods returns the movement associate with the WiiEvent
	 * @return A representation of the movement associate with the WiiEvent instance.
	 */
	MoveAction getMoveAction();

private:
	MoveAction moveType;
};

}
}
}
}
}

#endif /* WIIINPUTEVENT_H_ */
