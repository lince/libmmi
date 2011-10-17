#include "../../include/socketconn/SocketTCP.h"

#include <errno.h>
#include <cstring>

#define MAX_BUFFERSIZE  10240

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

DataPayload::DataPayload() {
	data = NULL;
	lenght = -1;
}

DataPayload::~DataPayload() {
	if (data) {
		delete data;
	}
}

SocketTCP::SocketTCP(string ip, unsigned short port) {
	logger = Logger::getInstance();
	logger->registerClass(this, "br::ufscar::lince::socketconn::SocketTCP");

	TRACE(logger, "Construtor Normal");

	this->portNumber = port;
	if (Functions::isIPv4(ip.c_str())) {
		this->ipAddress = ip;
	} else {
		throw IllegalParameterException("SocketTCP::SocketTCP(string ip, unsigned short port)\n"
				"'" + ip + "' is not a valid IPv4 address\n.",
				"br::ufscar::lince::mmi::socketconn::SocketTCP",
				"SocketTCP(string, unsigned short");
	}
	_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("SocketTCP::SocketTCP(string ip, unsigned short port)\n"
				"Socket couldn't be created:" + errMsg + "\n",
				"br::ufscar::lince::mmi::socketconn::SocketTCP",
				"SocketTCP(string, unsigned short");
	}

	memset(&addres, 0, sizeof(addres));

	addres.sin_family = AF_INET;
	addres.sin_port = htons(port);
	inet_aton(ip.c_str(), &(addres.sin_addr));
	isConnected = false;
}

SocketTCP::SocketTCP(int clientSocket, sockaddr_in clientAddres) {
	logger = Logger::getInstance();
	logger->registerClass(this, "br::ufscar::lince::socketconn::SocketTCP");

	TRACE(logger, "Construtor Friend");

	this->_socket = clientSocket;
	this->portNumber = ntohs(clientAddres.sin_port);
	in_addr inAddr = clientAddres.sin_addr;
	char* buffer = inet_ntoa(inAddr);
	ipAddress = buffer;
	isConnected = true;
}

void SocketTCP::connectSocket() {
	TRACE(logger, "connectSocket()");

	if (isConnected) {
		throw InitializationException("void SocketTCP::connectSocket()\n"
				"Socket is already connected.",
				"br::ufscar::lince::mmi::socketconn::SocketTCP",
				"connectSocket()");
	}
	int ret = connect(_socket, (struct sockaddr *) &addres, sizeof(addres));
	if (ret < 0) {
		string errMsg = strerror(errno);
		throw NetworkException("void SocketTCP::connectSocket()\n"
				"Couldn't connect:" + errMsg  + "\n",
				"br::ufscar::lince::mmi::socketconn::SocketTCP",
				"connectSocket()");
	}
	isConnected = true;
}

DataPayload* SocketTCP::reciveData() {
	TRACE(logger, "reciveData()");

	unsigned char* buffer = new unsigned char[MAX_BUFFERSIZE];
	int bytes = recv(_socket, buffer, MAX_BUFFERSIZE-1, 0);
	if (bytes <= 0) {
		string errMsg = strerror(errno);
		throw NetworkException("reciveData* SocketTCP::recive()\n"
				"Error while receiving data:" + errMsg  + "\n",
				"br::ufscar::lince::mmi::socketconn::SocketTCP",
				"reciveData()");
	}
	DataPayload* datap = new DataPayload();
	datap->data = new unsigned char [bytes];
	memcpy(datap->data, buffer, bytes);
	datap->lenght = bytes;
	return datap;
}

int SocketTCP::sendData(DataPayload* data) {
	TRACE(logger, "sendData()");

	int bytes = send(_socket, data->data, data->lenght, 0);
	if (bytes < 0) {
		if (bytes < 0) {
			string errMsg = strerror(errno);
			throw NetworkException("int sendData::send(DataPayload* data) \n"
					"Error while sending data:" + errMsg + "\n",
					"br::ufscar::lince::mmi::socketconn::SocketTCP",
					"sendData(DataPayload* )");
		}
	}
	return bytes;
}

string SocketTCP::getIPAddress() {
	return this->ipAddress;
}

unsigned short SocketTCP::getPortNumber() {
	return this->portNumber;
}

void SocketTCP::closeConnection() {
	close(_socket);
}

}
}
}
}
}
