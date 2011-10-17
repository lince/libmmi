#include "../include/EventBuffer.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

	EventBuffer::EventBuffer() {
		buffer = new vector<MMIEvent*>();
		waiting = false;

		logger = Logger::getInstance();
		logger->registerClass(this, "br::ufscar::lince::mmi::EventBuffer");
		TRACE(logger, "Constructor");

		pthread_mutex_init(&bufferlock, NULL);
	}

	void EventBuffer::lock() {
		//LoggerUtil_info(logger, "Entrando no lock");
		pthread_mutex_lock(&bufferlock);
		//LoggerUtil_info(logger, "Saindo no lock");
	}

	void EventBuffer::unlock() {
		//LoggerUtil_info(logger, "Entrando no unlock");
		pthread_mutex_unlock(&bufferlock);
		//LoggerUtil_info(logger, "Saindo no unlock");
	}

	EventBuffer::~EventBuffer() {
		lock();
		vector<MMIEvent*>::iterator it;
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
		//LoggerUtil_info(logger, "EventBuffer::postEvent");
		lock();
		buffer->push_back(event);
		unlock();
	}

	void EventBuffer::waitEvent() {
		//LoggerUtil_info(logger, "EventBuffer::waitEvent");
		waiting = true;
		while (buffer->size() == 0 && waiting) {
			//LoggerUtil_info(logger, "waiting: "<<waiting<<" bufSize: "<<buffer->size());
			usleep(10000);
		}
	}

	MMIEvent* EventBuffer::getNextEvent() {
		//LoggerUtil_info(logger, "EventBuffer::getNextEvent");
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
