#ifndef SERVERSOCKETTPC_H_
#define SERVERSOCKETTPC_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>

#include <libcpputil/Functions.h>
#include <libcpputil/InitializationException.h>
#include <libcpputil/IllegalParameterException.h>
#include <libcpputil/network/NetworkException.h>
#include <libcpputil/logger/Logger.h>

#include "SocketTCP.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class ServerSocketTCP : public cpputil::logger::Loggable {
public:
	ServerSocketTCP(unsigned short port);

	virtual ~ServerSocketTCP();

	void bindPort();
	void startListen();
	void startListen(unsigned int max);
	cpputil::network::SocketTCP* acceptConnection();
	void releasePort();

protected:
	unsigned short portNumber;

private:
	int serverSocket;
	sockaddr_in serverAddress;
	bool isBinded;

};

}
}
}
}
}

#endif /*SERVERSOCKETTPC_H_*/
