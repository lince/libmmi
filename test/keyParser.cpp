#include <mmi/EventParser.h>
#include <mmi/MMIEvent.h>
#include <mmi/KeyEvent.h>

using namespace ::br::ufscar::lince::mmi;

int main() {
	EventParser* eventParser = EventParser::getInstance();
	//data->payload = "/home/caioviel/Desktop/keyXMLEvent.xml";
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
		"</multimodal>\n";

	XMLData* data = new XMLData();
	data->payload = (char*) xml.c_str();
	data->length = xml.length();

	MMIEvent* event = eventParser->ParseXMLEvent(data);
	cout<<"eventType: "<<event->getEventType()<<endl;
	if (event->getEventType() == "key") {
		KeyEvent* key = (KeyEvent*) event;
		cout<<"key value: "<<key->getKeyId()<<endl;
	}
}
