#ifndef SERVERSOCKETTPC_H_
#define SERVERSOCKETTPC_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;

#include <cpputil/Functions.h>
#include <cpputil/InitializationException.h>
#include <cpputil/IllegalParameterException.h>
using namespace cpputil;

#include <cpputil/network/NetworkException.h>
using namespace cpputil::network;

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include "SocketTCP.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class ServerSocketTCP : public Loggable {
public:
	ServerSocketTCP(unsigned short port);

	virtual ~ServerSocketTCP();

	void bindPort();
	void startListen();
	void startListen(unsigned int max);
	SocketTCP* acceptConnection();
	void releasePort();

protected:
	unsigned short portNumber;

private:
	int serverSocket;
	sockaddr_in serverAddress;
	bool isBinded;
	Logger* logger;

};

}
}
}
}
}

#endif /*SERVERSOCKETTPC_H_*/
