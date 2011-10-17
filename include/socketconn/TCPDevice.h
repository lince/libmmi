#ifndef TCPDEVICE_H_
#define TCPDEVICE_H_

#include <cpputil/Thread.h>
using namespace cpputil;

#include "../IDeviceComm.h"
#include "../MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

#include "SocketTCP.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class TCPDevice : public IDeviceComm, public Thread {
public:
	TCPDevice(SocketTCP* socket);

	virtual ~TCPDevice();

	void connect();

	void disconnect();

	void sendToDevice(vector<string>* args);

	string getDeviceId();

	void release();

	string getDeviceIP();

	unsigned short getDevicePort();

private:

	void run();

	bool running;

	string deviceId;

	SocketTCP* nsocket;

	MMIManager* manager;
};


}
}
}
}
}

#endif /* TCPDEVICE_H_ */
