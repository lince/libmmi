#include <iostream>
using namespace std;

#include "../../include/socketconn/TCPCommServer.h"
#include "../../include/socketconn/TCPDevice.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

TCPCommServer::TCPCommServer(int portnumber) {
	this->portnumber = portnumber;
	serverSocket = NULL;
	running = false;
}

TCPCommServer::~TCPCommServer() {
	release();
}

void TCPCommServer::release() {
	if (serverSocket != NULL) {
		serverSocket->releasePort();
		delete serverSocket;
		serverSocket = NULL;
	}
}

void TCPCommServer::handleConnection(SocketTCP* socket) {
	TCPDevice* device = new TCPDevice(socket);
}

void TCPCommServer::run() {
	running = true;
	try {
		serverSocket = new ServerSocketTCP(portnumber);
		serverSocket->bindPort();
		serverSocket->startListen();

		while (running) {
			SocketTCP* connection = serverSocket->acceptConnection();
			handleConnection(connection);
		}
	} catch(NetworkException &except) {
		cerr<<"Exception Catch in TCPCommServer::run(): "<<except.what();
		goto Finaly;
	} catch(IllegalParameterException &except) {
		cerr<<"Exception Catch in TCPCommServer::run(): "<<except.what();
		goto Finaly;
	} catch(InitializationException &except) {
		cerr<<"Exception Catch in TCPCommServer::run(): "<<except.what();
		goto Finaly;
	}
	Finaly: {
		release();
	}
}


}
}
}
}
}
