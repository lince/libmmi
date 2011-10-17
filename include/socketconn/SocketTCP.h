#ifndef CLIENTSOCKETTCP_H_
#define CLIENTSOCKETTCP_H_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
using namespace std;

#include <cpputil/Functions.h>
#include <cpputil/InitializationException.h>
#include <cpputil/IllegalParameterException.h>
using namespace cpputil;

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include <cpputil/network/NetworkException.h>
using namespace cpputil::network;


namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

class DataPayload {
public:
	DataPayload();
	~DataPayload();

	int lenght;
	unsigned char* data;
};

class ServerSocketTCP;

class SocketTCP : public Loggable {
public:
	SocketTCP(string ip, unsigned short port);
	void connectSocket();
	DataPayload* reciveData();
	int sendData(DataPayload* data);
	void closeConnection();

	string getIPAddress();
	unsigned short getPortNumber();

protected:
	SocketTCP(int clientSocket, sockaddr_in clientAddres);

private:
	int _socket;
	string ipAddress;
	unsigned short portNumber;
	sockaddr_in addres;
	bool isConnected;
	Logger* logger;

friend class ServerSocketTCP;
};

}
}
}
}
}

#endif /*CLIENTSOCKETTCP_H_*/
