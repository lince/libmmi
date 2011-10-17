/*
 * WiiDriver.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef WIIDRIVER_H_
#define WIIDRIVER_H_

#include <cwiid.h>
#include <iostream>
using namespace std;

#include <cpputil/InitializationException.h>
using namespace cpputil;


#include "WiiState.h"


namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class WiiDriver {
public:
	WiiDriver();
	virtual ~WiiDriver();

	WiiState* getCurrentState();
	bool isButtonsSetted();
	bool isAccelerometerSetted();
	bool isInfraredSetted();
	void setButtons(bool b);
	void setAccelerometer(bool b);
	void setInfrared(bool b);
	void connect();

private:
    cwiid_wiimote_t *wiimote;
    unsigned char reportMode;
};

}
}
}
}
}

#endif /* WIIDRIVER_H_ */
