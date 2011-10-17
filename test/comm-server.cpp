#include <iostream>
#include <set>
using namespace std;

#include <mmi/MMIManager.h>
#include <mmi/MMIEventListener.h>
#include <mmi/KeyEvent.h>
using namespace ::br::ufscar::lince::mmi;

class EventHandler : public MMIEventListener {
	virtual bool receiveEvent(MMIEvent* event);
};

bool EventHandler::receiveEvent(MMIEvent* event) {
	if (event->getEventType() == "key") {
		KeyEvent* key = (KeyEvent*) event;
		cout<< "Evento:" << key->getKeyId() << endl;
	}
	return true;
}

int main() {
	MMIManager* manager = MMIManager::getInstance();
	EventHandler* handler = new EventHandler();
	set<string>* events = new set<string>();
	events->insert("key");

	manager->addEventListener(handler, events);

	while(true) {
		sleep(50000);
	}
}
