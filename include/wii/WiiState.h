/*
 * WiiState.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef WIISTATE_H_
#define WIISTATE_H_

#include <cwiid.h>

#include <cpputil/IllegalParameterException.h>
using namespace cpputil;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

enum ButtonsId {BUTTON_A, BUTTON_B, BUTTON_1,
	BUTTON_2, BUTTON_PLUS, BUTTON_MINUS, BUTTON_HOME,
	BUTTON_UP, BUTTON_DOWN, BUTTON_LEFT, BUTTON_RIGHT};

class WiiState {
public:
    WiiState(WiiState* copy);
    WiiState(cwiid_state nState);
    WiiState();
	virtual ~WiiState();
    int getAccelationX();
    int getAccelationY();
    int getAccelationZ();
    int getInfraredX(int indice);
    int getInfraredY(int indice);
    int getInfraredZ(int indice);
    bool isButtonPressed(ButtonsId buttonId);

private:
    struct cwiid_state state;
};

}
}
}
}
}

#endif /* WIISTATE_H_ */
