/*
 * WiiMote.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef WIIMOTE_H_
#define WIIMOTE_H_

#include <cpputil/Thread.h>
using namespace cpputil;

#include <math.h>
#include <cwiid.h>
#include <unistd.h> //header para usar a função usleep
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "../AccelerationEvent.h"
#include "../IDeviceComm.h"
#include "../MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

#include "WiiDriver.h"
#include "WiiState.h"
#include "WiiEventHandler.h"
#include "WiiEvent.h"
#include "StateCircularBuffer.h"
#include "WiiButtonReport.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class WiiMote : public Thread, public IDeviceComm {
public:
	static const unsigned char REPORT_BUTTONS;
	static const unsigned char REPORT_ACCELERATION;
	static const unsigned char REPORT_MOVES;
	static const unsigned char REPORT_ALL;

public:
	WiiMote(WiiEventHandler* handler,
			unsigned char reportEvents = REPORT_ALL);

	virtual ~WiiMote();

	virtual void connect();

	virtual void disconnect();

	virtual void sendToDevice(vector<string>* args);

	virtual string getDeviceId();

	virtual void release();

	inline bool isReportingButtons();

	inline bool isReportingAcceleration();

	inline bool isReportingMoves();

private:
	unsigned char reportEvents;
	WiiEventHandler* handler;

	WiiButtonReport* buttonReport;
	WiiDriver *wiiDriver;
	StateCircularBuffer* buffer;
	string deviceName;

    time_t tempoi, tempof;
    double tempoTotal;
protected:
    int evalueMassCenterAccX();
    int evalueMassCenterAccY();
    int evalueMassCenterAccZ();

    virtual void run();
};

}
}
}
}
}

#endif /* WIIMOTE_H_ */
