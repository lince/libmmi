/*
 * test1.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include <mmi/MMIEventListener.h>
#include <mmi/MMIManager.h>
#include <mmi/MMIEvent.h>
#include <mmi/AccelerationEvent.h>
#include <mmi/KeyEvent.h>
using namespace br::ufscar::lince::mmi;

#include <mmi/wii/WiiMote.h>
#include <mmi/wii/WiiEvent.h>
#include <mmi/wii/WiiEventPoster.h>
using namespace br::ufscar::lince::mmi::wii;

#include <iostream>
#include <set>
#include <string>

class EvListener : public MMIEventListener {
public:
	bool receiveEvent(MMIEvent* event);

	EvListener();

};

EvListener::EvListener() {

}

bool EvListener::receiveEvent(MMIEvent* event) {
	string t = event->getEventType();
	string d = event->getDeviceId();
	cout<<"Chegou do Device: "<<d<<" o efeito do tipo: "<<t<<endl;

	if (t == "button") {
		KeyEvent* b = (KeyEvent*)event;
		cout<<b->getKeyId()<<endl;
		if (b->getKeyId() == "WII_BUTTON_UP") {
			exit(0);
		}
	}

	if (t == "acceleration") {
		AccelerationEvent* acc = (AccelerationEvent*)event;
		cout<<"X: "<<acc->getXValue()<<"\t";
		cout<<"Y: "<<acc->getYValue()<<"\t";
		cout<<"Z: "<<acc->getZValue()<<endl;
	}

}


int main() {
	WiiMote* wiiMote = new WiiMote(
			new WiiEventPoster(), WiiMote::REPORT_ALL);

	wiiMote->connect();

	EvListener* evListener = new EvListener();
	set<string>* evType = new set<string>();
	evType->insert("button");
	evType->insert("wiiEvent");
	evType->insert("acceleration");

	MMIManager::getInstance()->addEventListener(evListener, evType);


	while(1) {
		usleep(1000000);
	}

	return 0;
}

