#include "../../include/wii/WiiButtonReport.h"
using namespace ::br::ufscar::lince::mmi;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiButtonReport::WiiButtonReport(string deviceId,
		WiiEventHandler* handler, WiiDriver* wiiDriver) : Thread() {

	this->deviceId = deviceId;
	this->handler = handler;
	this->wiiDriver = wiiDriver;
}

WiiButtonReport::~WiiButtonReport() {

}

void WiiButtonReport::run() {
	WiiState* state;
	while(1) {
		state = wiiDriver->getCurrentState();
		if (state->isButtonPressed(BUTTON_UP)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_UP"));
		} else if (state->isButtonPressed(BUTTON_DOWN)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_DOWN"));
		} else if (state->isButtonPressed(BUTTON_LEFT)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_LEFT"));
		} else if (state->isButtonPressed(BUTTON_RIGHT)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_RIGHT"));
		}

		if (state->isButtonPressed(BUTTON_PLUS)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_PLUS"));
		} else if (state->isButtonPressed(BUTTON_MINUS)) {
			handler->sendEvent(
					new KeyEvent(deviceId, "WII_BUTTON_MINUS"));
		}
		usleep(20);
	}

}

}
}
}
}
}
