/*
 * WiiDriver.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#include "../../include/wii/WiiDriver.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiDriver::WiiDriver() {
	this->reportMode = 0;
	this->wiimote = NULL;
}

WiiDriver::~WiiDriver() {
    if (wiimote != NULL)
    	if (cwiid_close(wiimote)) {
    		throw InitializationException(
	    		"Erro ao tentar desconectar do wiimote.",
	    		"br::ufscar::lince::mmi:wii::WiiDriver",
	    		"~WiiDriver");
	}
}

WiiState* WiiDriver::getCurrentState() {
	cwiid_state state;
	if (cwiid_get_state(wiimote, &state)) {
		throw InitializationException(
    		"Erro ao tentar obter o estado atual do WiiState.",
    		"br::ufscar::lince::mmi:wii::WiiDriver",
    		"getCurrentState()");
	}
	WiiState* wiiState = new WiiState(state);
	return wiiState;
}

void WiiDriver::setInfrared(bool b) {
	 if (b && (!(bool)(reportMode & CWIID_RPT_IR))) {
		 reportMode = reportMode | CWIID_RPT_IR;
	 } else if (!b && (reportMode & CWIID_RPT_IR)) {
	     reportMode = reportMode & (~CWIID_RPT_IR);
	 }
}

bool WiiDriver::isAccelerometerSetted() {
	return (bool)(reportMode & CWIID_RPT_ACC);
}

void WiiDriver::setButtons(bool b) {
	 if (b && (!(bool)(reportMode & CWIID_RPT_BTN))) {
		 reportMode = reportMode | CWIID_RPT_BTN;
	 } else if (!b && (reportMode & CWIID_RPT_BTN)) {
	     reportMode = reportMode & (~CWIID_RPT_BTN);
	 }
}

void WiiDriver::setAccelerometer(bool b) {
	 if (b && (!(bool)(reportMode & CWIID_RPT_ACC))) {
		 reportMode = reportMode | CWIID_RPT_ACC;
	 } else if (!b && (reportMode & CWIID_RPT_ACC)) {
	     reportMode = reportMode & (~CWIID_RPT_ACC);
	 }
}

bool WiiDriver::isButtonsSetted() {
	return (bool)(reportMode & CWIID_RPT_BTN);
}

bool WiiDriver::isInfraredSetted() {
	return (bool)(reportMode & CWIID_RPT_IR);
}

void WiiDriver::connect() {
	 bdaddr_t bdaddr = *BDADDR_ANY;

	 if (!(wiimote = cwiid_open(&bdaddr, 0))) {
	    throw InitializationException(
	    		"Erro ao tentar connectar ao wiimote.",
	    		"br::ufscar::lince::mmi:wii::WiiDriver",
	    		"connect()");
	 }

	if (cwiid_set_rpt_mode(wiimote, reportMode)) {
	    	throw InitializationException(
	    		"Erro durante a inicialização do wiimote.",
	    		"br::ufscar::lince::mmi:wii::WiiDriver",
	    		"connect()");
	}
}

}
}
}
}
}
