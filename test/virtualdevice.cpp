#include <mmi/socketconn/SocketTCP.h>
using namespace ::br::ufscar::lince::mmi::socketconn;

#include <iostream>
using namespace std;

int main() {
	SocketTCP* socket = new SocketTCP("127.0.0.1", 6004);
	socket->connectSocket();

	string xml = "<?xml version=\"1.0\"?>\n"
			"<multimodal xmlns=\"http://agua.intermidia.icmc.usp.br/intermidia\"\n"
			"xmlns:inkml=\"http://www.w3.org/2003/InkML\"\n"
			"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n"
			"xsi:schemaLocation=\"multimodal.xsd\"\n"
			"id=\"idDoEventoDeTeste\">\n"
			"<head>\n"
				"<device id=\"DEADBEEF-DEAF-BABA-FEED-BABE00000006\"\n"
				"		model=\"iPhone 3GS\"/>\n"
				"<user id=\"59616261-6461-6261-4E50-472050325033\"/>\n"
				"<timestamp begin=\"2010-05-19T09:30:10.5\" end=\"2010-05-19T09:30:17.8\"/>\n"
				"<eventType id=\"key\"/>\n"
			"</head>\n"
			"<body>\n"
				"<key>UP</key>\n"
			"</body>\n"
		"</multimodal>\0";

	DataPayload* data = new DataPayload();

	data->data  = (unsigned char*) xml.c_str();
	data->lenght = xml.length();

	cout << "Data enviada: " << (char*) data->data << endl;
	for (int i = 0; i < 10; i++) {
		socket->sendData(data);
		sleep(6);
	}
	socket->closeConnection();

}
