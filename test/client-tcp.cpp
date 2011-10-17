#include <mmi/socketconn/SocketTCP.h>
using namespace br::ufscar::lince::mmi::socketconn;

#include <iostream>
using namespace std;

int main() {
	try {
		SocketTCP* socket = new SocketTCP("127.0.0.1", 6004);
		socket->connectSocket();
		DataPayload* data;
		data = socket->reciveData();
		cout<< (char*) data->data <<endl;
		delete data;
		data = new DataPayload();
		data->data = (unsigned char*) "mensagem do cliente";
		data->lenght = 20;
		socket->sendData(data);
	} catch(NetworkException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	} catch(IllegalParameterException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	} catch(InitializationException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	}
	return 0;
}
