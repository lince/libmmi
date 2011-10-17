/*
 * StateCircularBuffer.cpp
 *
 *  Created on: Sep 1, 2010
 *      Author: caioviel
 */

#include "../../include/wii/StateCircularBuffer.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {
namespace wii {

WiiState* StateCircularBuffer::getBegin() {
	if (isEmpty()) {
		return NULL;
	}

	if (currentSize < maxSize) {
		iterator = begin;
	} else {
		iterator = end;
		iterationCount = 0;
	}
	return buffer[iterator];
}

WiiState* StateCircularBuffer::getNext() {
	if (currentSize < maxSize) {
		iterator = ajust(iterator+1);
		if (iterator != end) {
			return buffer[iterator];
		}
	} else {
		iterationCount++;
		iterator = ajust(iterator+1);
		if (iterationCount < maxSize) {
			return buffer[iterator];
		}
	}
	return NULL;
}

StateCircularBuffer::StateCircularBuffer(int size) {
	this->maxSize = size;
	this->currentSize = 0;
	this->begin = 0;
	this->end = 0;
	buffer = new WiiState*[maxSize];
}

StateCircularBuffer::~StateCircularBuffer() {
   delete buffer;
}

int StateCircularBuffer::getMaxSize() {
	return maxSize;
}

bool StateCircularBuffer::isEmpty() {
	return (this->currentSize == 0);
}

void StateCircularBuffer::showAllStates() {
	if (isEmpty()) {
		cout<<"Vazia"<<endl;
		return;
	}

	cout<<"Ordem Lógica: ";
	if (currentSize < maxSize) {
		for (int aux = begin; aux != end; aux = ajust(aux+1)) {
			cout<<buffer[aux]->getAccelationX()<<"\t";
		}
	} else {
		for (int aux = end, i = 0; i < maxSize; aux = ajust(aux+1), i++) {
			cout<<buffer[aux]->getAccelationX()<<"\t";
		}
	}
	cout<<endl;

	cout<<"Ordem Física: ";
	for (int i = 0; i < maxSize; i++) {
		cout<<buffer[i]->getAccelationX()<<"\t";
	}
	cout<<endl<<endl;
}

void StateCircularBuffer::insert(WiiState* state) {

	buffer[end] = state;
	end = ajust(end+1);
	if (end == begin) {
		delete buffer[begin];
		begin = ajust(begin+1);
	}
	if (currentSize < maxSize) {
		currentSize++;
	}
}

int StateCircularBuffer::getCurrentSize() {
	return currentSize;
}

WiiState* StateCircularBuffer::remove() {
	if (!isEmpty()) {
		WiiState* aux = buffer[ajust(end -1)];
		end = ajust(end-1);
		if (end < begin) {
			begin = ajust(begin -1);
		}
		currentSize--;
		return aux;
	}
	currentSize--;
	return NULL;
}

WiiState* StateCircularBuffer::take() {
	if (!isEmpty()) {
		return buffer[ajust(end -1)];
	}
	return NULL;
}

int StateCircularBuffer::ajust(int index) {
	if (index >= 0 && index < maxSize) {
		return index;
	} else if (index >= maxSize) {
		return index%maxSize;
	} else { /*index < 0*/
		return (maxSize + index);
	}
}

}
}
}
}
}
