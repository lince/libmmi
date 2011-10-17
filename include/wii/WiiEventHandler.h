#ifndef WIIEVENTHANDLER_H_
#define WIIEVENTHANDLER_H_

#include "../MMIEvent.h"
using namespace ::br::ufscar::lince::mmi;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class WiiEventHandler {
public:
	virtual void sendEvent(MMIEvent* event)=0;
	virtual ~WiiEventHandler() {};
};

}
}
}
}
}

#endif /*WIIEVENTHANDLER_H_*/
