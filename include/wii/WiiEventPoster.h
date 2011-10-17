/*
 * WiiEventPoster.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef WIIEVENTPOSTER_H_
#define WIIEVENTPOSTER_H_

#include "../MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

#include "WiiEventHandler.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class WiiEventPoster : public WiiEventHandler {
public:
	WiiEventPoster();
	virtual ~WiiEventPoster();
	void sendEvent(MMIEvent* event);

private:
	MMIManager* mmimanager;
};

}
}
}
}
}

#endif /* WIIEVENTPOSTER_H_ */
