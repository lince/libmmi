#ifndef TCPCONNSERVER_H_
#define TCPCONNSERVER_H_

#define DEFAULT_PORT	6004

#include <cpputil/Thread.h>
using namespace cpputil;

#include "ServerSocketTCP.h"
#include "SocketTCP.h"
#include "TCPDevice.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class TCPCommServer : public Thread {
public:
	TCPCommServer(int portnumber = DEFAULT_PORT);
	~TCPCommServer();

	void release();

private:
	bool running;
	void handleConnection(SocketTCP* socket);
	void run();
	int portnumber;

	ServerSocketTCP* serverSocket;
};

}
}
}
}
}

#endif /*TCPCONNSERVER_H_*/
