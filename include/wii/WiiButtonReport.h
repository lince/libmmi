#ifndef WIIBUTTONPARSER_H_
#define WIIBUTTONPARSER_H_

#include <math.h>
#include <cwiid.h>
#include <unistd.h> //header para usar a função usleep
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../KeyEvent.h"
using namespace ::br::ufscar::lince::mmi;

#include "WiiDriver.h"
#include "WiiState.h"
#include "WiiEventHandler.h"


#include <cpputil/Thread.h>
using namespace cpputil;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class WiiButtonReport : public Thread {
public:
	WiiButtonReport(string deviceId, WiiEventHandler* handler, WiiDriver* wiiDriver);
	~WiiButtonReport();
	virtual void run();

private:
	WiiEventHandler* handler;
	WiiDriver *wiiDriver;
	string deviceId;

};


}
}
}
}
}

#endif /*WIIBUTTONPARSER_H_*/
