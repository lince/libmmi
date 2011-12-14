#ifndef TCPDEVICE_H_
#define TCPDEVICE_H_

#include <libcpputil/Thread.h>

#include "../IDeviceComm.h"
#include "../MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

#include "SocketTCP.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class TCPDevice : public IDeviceComm, public cpputil::Thread {
public:
	TCPDevice(SocketTCP* socket);

	virtual ~TCPDevice();

	virtual void connect();

	virtual void disconnect();

	virtual void sendToDevice(vector<string>* args);

	virtual string getDeviceId();

	virtual void release();

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
