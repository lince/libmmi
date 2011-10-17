#include "../../include/socketconn/ServerSocketTCP.h"

#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>

#define MAX_BAKCLOG	128

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

ServerSocketTCP::ServerSocketTCP(unsigned short port) {
	logger = Logger::getInstance();
	logger->registerClass(this, "br::ufscar::lince::util::ServerSocketTCP");

	TRACE(logger, "Construtor");

	this->portNumber = port;

	serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("ServerSocketTCP::ServerSocketTCP(unsigned short port)\n"
				"Server Socket couldn't be created:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"ServerSocket(unsigned short");
	}

	memset((void*)& serverAddress, 0, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(portNumber);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	isBinded = false;
}

ServerSocketTCP::~ServerSocketTCP() {
	TRACE(logger, "Destrutor");

	close(serverSocket);
}

void ServerSocketTCP::bindPort() {
	TRACE(logger, "bindPort()");

	if (bind(serverSocket, (struct sockaddr *) &serverAddress,
			sizeof(serverAddress)) < 0) {

		string errMsg = strerror(errno);
		throw NetworkException("void bindPort::bindPort()\n"
				"Couldn't realize the binding:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"bindPort()");
	}
	isBinded = true;
}

void ServerSocketTCP::startListen() {
	TRACE(logger, "startListen()");

	if (listen(serverSocket, MAX_BAKCLOG) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("void ServerSocketTCP::startListen()\n"
				"Error while listening for connections:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"startListen()");
	}
}

void ServerSocketTCP::startListen(unsigned int max) {
	TRACE(logger, "startListen(unsigned int max)");

	if (max > 128) {
		throw IllegalParameterException("void ServerSocketTCP::startListen(unsigned int max)\n"
				"Tried a backlog number bigger than the maximum allowed (128).\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"startListen(unsigned int)");
	}
	if (listen(serverSocket, MAX_BAKCLOG) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("void ServerSocketTCP::startListen(unsigned int max)\n"
				"Error while listening for connections:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"startListen(unsigned int)");
	}
}

SocketTCP* ServerSocketTCP::acceptConnection() {
	TRACE(logger, "acceptConnection()");

	sockaddr_in clientAddres;
	int size = sizeof(clientAddres);
	int client = accept(serverSocket,
			(struct sockaddr *) &clientAddres, (socklen_t*) &size);

	if (client < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("SocketTCP* ServerSocketTCP::acceptConnection()\n"
				"Error trying to accept connections:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"acceptConnection()");
	}

	return new SocketTCP(client, clientAddres);
}

void ServerSocketTCP::releasePort() {
	TRACE(logger, "releasePort()");

	if (!isBinded) {
		throw InitializationException("void ServerSocketTCP::releasePort()\n"
						"Try to release port, but port hasn't binded yet.\n",
						"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
						"releasePort()");
	}

	if (shutdown(serverSocket, SHUT_RDWR) < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("void ServerSocketTCP::releasePort()\n"
				"Error trying to release the port:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::ServerSocketTCP",
				"releasePort()");
	}
}

}
}
}
}
}
