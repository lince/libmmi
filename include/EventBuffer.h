#ifndef EVENTBUFFER_H_
#define EVENTBUFFER_H_

#include <vector>
using namespace std;

#include "MMIEvent.h"

#include <cpputil/Thread.h>
using namespace cpputil;

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

	class EventBuffer : public Loggable {
		private:
			vector<MMIEvent*>* buffer;
			bool waiting;
			pthread_mutex_t bufferlock;
			Logger* logger;
		protected:
			void lock();
			void unlock();

		public:
			EventBuffer();
			~EventBuffer();
			void wakeUp();
			void postEvent(MMIEvent* event);
			void waitEvent();
			MMIEvent* getNextEvent();
	};
}
}
}
}


#endif /*EVENTBUFFER_H_*/
