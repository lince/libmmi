#include <mmi/socketconn/ServerSocketTCP.h>
using namespace br::ufscar::lince::mmi::socketconn;

#include <iostream>
using namespace std;

void handleConnection(SocketTCP* connection) {
	DataPayload* data = new DataPayload();
	data->data = (unsigned char*) "mensagem do servidor";
	data->lenght = 21;
	try {
		connection->sendData(data);
		//delete data;
		data = connection->reciveData();
		cout<< (char*) data->data <<endl;
	} catch(NetworkException except) {
		cerr<<"Exception Catch in handleConnection: "<<except.what();
	} catch(IllegalParameterException except) {
		cerr<<"Exception Catch in handleConnection: "<<except.what();
	} catch(InitializationException except) {
		cerr<<"Exception Catch in handleConnection: "<<except.what();
	}
}

int main() {
	try {
		ServerSocketTCP* server = new ServerSocketTCP(2001);
		server->bindPort();
		cout<<"Server listening on port 2001 ..."<<endl;
		server->startListen();
		SocketTCP* connection = server->acceptConnection();
		handleConnection(connection);
		server->releasePort();

	} catch(NetworkException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	} catch(IllegalParameterException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	} catch(InitializationException except) {
		cerr<<"Exception Catch in Main: "<<except.what();
	}
	return 0;
}
