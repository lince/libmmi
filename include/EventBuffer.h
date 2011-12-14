#ifndef EVENTBUFFER_H_
#define EVENTBUFFER_H_

#include <vector>

#include "MMIEvent.h"

#include <libcpputil/Thread.h>
#include <libcpputil/logger/Logger.h>

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

	class EventBuffer : public cpputil::logger::Loggable {
		private:
			std::vector<MMIEvent*>* buffer;
			bool waiting;
			pthread_mutex_t bufferlock;
		protected:
			void lock();
			void unlock();

		public:
			EventBuffer();
			virtual ~EventBuffer();
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
