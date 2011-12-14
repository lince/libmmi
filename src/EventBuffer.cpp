#include "../include/EventBuffer.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

EventBuffer::EventBuffer()
		: cpputil::logger::Loggable("br::ufscar::lince::mmi::EventBuffer") {

	trace(" begin Constructor");

	pthread_mutex_init(&bufferlock, NULL);
}

void EventBuffer::lock() {
	pthread_mutex_lock(&bufferlock);
}

void EventBuffer::unlock() {
	pthread_mutex_unlock(&bufferlock);;
}

EventBuffer::~EventBuffer() {
	lock();
	std::vector<MMIEvent*>::iterator it;
	for (it = buffer->begin(); it != buffer->end(); it++) {
		delete &it;
	}
	delete buffer;
	unlock();
	pthread_mutex_destroy(&bufferlock);
}

void EventBuffer::wakeUp() {
	waiting = false;
}

void EventBuffer::postEvent(MMIEvent* event) {
	lock();
	buffer->push_back(event);
	unlock();
}

void EventBuffer::waitEvent() {
	waiting = true;
	while (buffer->size() == 0 && waiting) {
		usleep(10000);
	}
}

MMIEvent* EventBuffer::getNextEvent() {
	lock();
	if (buffer->size() == 0) {
		unlock();
		return NULL;
	} else {
		MMIEvent* event = *(
				buffer->erase(buffer->begin()));

		unlock();
		return event;
	}
}

}
}
}
}
