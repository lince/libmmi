#include "../../include/socketconn/TCPDevice.h"

#include <cpputil/network/NetworkException.h>
using namespace cpputil::network;

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {
namespace socketconn {

TCPDevice::TCPDevice(SocketTCP* nsocket) : Thread() {
	manager = MMIManager::getInstance();

	this->nsocket = nsocket;
	//DataPayload* data = socket->reciveData();
	//parseDeviceInfo(data);
	running = true;
	Thread::start();
}

TCPDevice::~TCPDevice() {

}

void TCPDevice::connect() {
	//TODO: throw expcetion
}

void TCPDevice::disconnect() {
	running = false;
}

void TCPDevice::sendToDevice(vector<string>* args) {

}

string TCPDevice::getDeviceId() {
	return deviceId;
}

void TCPDevice::release() {

}

string TCPDevice::getDeviceIP() {
	return nsocket->getIPAddress();
}

unsigned short TCPDevice::getDevicePort() {
	return nsocket->getPortNumber();

}

void TCPDevice::run() {
	DataPayload* data;
	while (running) {
		try {
			data = nsocket->reciveData();
			cout<<"Data Recived: "<< (char*) data->data <<endl;
			cout<<"size: " << data->lenght <<endl;
			XMLData* xmlData = new XMLData();
			xmlData->payload = (char*) data->data;
			xmlData->length = data->lenght;
			manager->postXMLEvent(xmlData);
		} catch(NetworkException &e) {
			cerr<<"Conection closed."<< e.what() <<endl;
			running = false;
		}
	}
}

}
}
}
}
}
