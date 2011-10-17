/*
 * WiiEventPoster.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#include "../../include/wii/WiiEventPoster.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiEventPoster::WiiEventPoster() {
	mmimanager = MMIManager::getInstance();
}

WiiEventPoster::~WiiEventPoster() {
	// TODO Auto-generated destructor stub
}

void WiiEventPoster::sendEvent(MMIEvent* event) {
	mmimanager->postEvent(event);
}

}
}
}
}
}
