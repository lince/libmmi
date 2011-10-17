/*
 * StateCircularBuffer.h
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#ifndef STATECIRCULARBUFFER_H_
#define STATECIRCULARBUFFER_H_

#include <iostream>
using namespace std;

#include "WiiState.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

class StateCircularBuffer {
public:
	StateCircularBuffer(int size=10);
	virtual ~StateCircularBuffer();

	int getCurrentSize();
	int getMaxSize();
	void insert(WiiState* state);
	WiiState* remove();
	WiiState* take();
	bool isEmpty();
	void showAllStates();

	WiiState* getBegin();
	WiiState* getNext();

private:
	int maxSize;
	int currentSize;
	WiiState** buffer;
	int begin;
	int end;
	int iterator;
	int iterationCount;
	int ajust(int index);
};

}
}
}
}
}

#endif /* STATECIRCULARBUFFER_H_ */
