/*
 * WiiState.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#include "../../include/wii/WiiState.h"

#include <cwiid.h>

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiState::WiiState(WiiState *copy) {
	state = copy->state;
}

WiiState::WiiState(cwiid_state nState) {
	state = nState;

}

WiiState::WiiState() {

}

WiiState::~WiiState() {

}

int WiiState::getAccelationX() {
	return state.acc[CWIID_X];
}


int WiiState::getAccelationY() {
	return state.acc[CWIID_Y];
}

int WiiState::getAccelationZ() {
	return state.acc[CWIID_Z];
}

int WiiState::getInfraredX(int indice) {
	if (indice >=0 && indice <= 7) {
		return state.ir_src[indice].pos[CWIID_X];
	} else {
		throw IllegalParameterException(
				"Tentando acessar um infrared inválido!",
				"br::ufscar::lince::mmi::wii::WiiState",
				"getInfraredX(int )");
	}
}

int WiiState::getInfraredY(int indice) {
	if (indice >=0 && indice <= 7) {
		return state.ir_src[indice].pos[CWIID_Y];
	} else {
		throw IllegalParameterException(
				"Tentando acessar um infrared inválido!",
				"br::ufscar::lince::mmi::wii::WiiState",
				"getInfraredY(int )");
	}
}

int WiiState::getInfraredZ(int indice) {
	if (indice >=0 && indice <= 7) {
		return state.ir_src[indice].pos[CWIID_Z];
	} else {
		throw IllegalParameterException(
				"Tentando acessar um infrared inválido!",
				"br::ufscar::lince::mmi::wii::WiiState",
				"getInfraredY(int )");
	}
	return 0; //truly unnecessary
}


bool WiiState::isButtonPressed(ButtonsId buttonId) {
	if (buttonId == BUTTON_A) {
		return (bool) (state.buttons & CWIID_BTN_A);
	} else if (buttonId == BUTTON_B) {
		return (bool) (state.buttons & CWIID_BTN_B);
	} else if (buttonId == BUTTON_1) {
		return (bool) (state.buttons & CWIID_BTN_1);
	} else if (buttonId == BUTTON_2) {
		return (bool) (state.buttons & CWIID_BTN_2);
	} else if (buttonId == BUTTON_HOME) {
		return (bool) (state.buttons & CWIID_BTN_HOME);
	} else if (buttonId == BUTTON_PLUS) {
		return (bool) (state.buttons & CWIID_BTN_PLUS);
	} else if (buttonId == BUTTON_MINUS) {
		return (bool) (state.buttons & CWIID_BTN_MINUS);
	}  else if (buttonId == BUTTON_UP) {
		return (bool) (state.buttons & CWIID_BTN_UP);
	} else if (buttonId == BUTTON_DOWN) {
		return (bool) (state.buttons & CWIID_BTN_DOWN);
	} else if (buttonId == BUTTON_LEFT) {
		return (bool) (state.buttons & CWIID_BTN_LEFT);
	} else if (buttonId == BUTTON_RIGHT) {
		return (bool) (state.buttons & CWIID_BTN_RIGHT);
	}
	return false;
}

}
}
}
}
}
