/*
 * MMIEventListener.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef MMIEVENTLISTENER_H_
#define MMIEVENTLISTENER_H_

#include "MMIEvent.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

/**
 * This abstract class represents a instance that can listen to MultimodalE vents.
 * Any application that wish be notified when a Multimodal Events occurs must
 * implement this class and register a instance in the MMIManager. Everytime
 * a Multimodal Event occurs, the methods receiveEvent of that instance will be called
 * by the MIIManager.
 */
class MMIEventListener {
public:
	/**
	 * Generic Destructor
	 */
	virtual ~MMIEventListener() {};

	/**
	 * This method receives multimodal events when they occurs
	 * @param event The multimodal event that occurs.
	 */
	virtual bool receiveEvent(MMIEvent* event) = 0;
};

}
}
}
}


#endif /* MMIEVENTLISTENER_H_ */
