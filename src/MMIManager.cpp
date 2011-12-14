/*
 * MMIManager.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#include "../include/socketconn/TCPCommServer.h"
using namespace ::br::ufscar::lince::mmi::socketconn;

#include "../include/zeroconf/CommunicationManager.h"
using namespace ::br::ufscar::lince::mmi::zeroconf;

#include "../include/wii/WiiEventPoster.h"
#include "../include/wii/WiiMote.h"
using namespace ::br::ufscar::lince::mmi::wii;

//#include "../include/MMIService.h"
//using namespace ::br::ufscar::lince::mmi::upnp;

#include "../include/MMIManager.h"

using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

MMIManager* MMIManager::_instance = NULL;

MMIManager::MMIManager() : cpputil::logger::Loggable("br::ufscar::lince::mmi::MMIManager") {
	trace("begin constructor");

	intervalTime = 5;
	running = true;
	notifying = false;

	eventBuffer = new EventBuffer();
	eventListeners = new map<MMIEventListener*, set<string>*>();
	pthread_mutex_init(&eventListenerMutex, NULL);

	devices = new map<string, IDeviceComm*>();
	pthread_mutex_init(&devicesMutex, NULL);

	actionsToMultimodalListeners = new vector<LockedMultimodalAction*>;
	pthread_mutex_init(&actMultimodalMutex, NULL);

	eventParser = EventParser::getInstance();

	TCPCommServer* tcpCommServer = new TCPCommServer();
	tcpCommServer->start();

	CommunicationManager* commManager = CommunicationManager::getInstance();
	commManager->start();

	//MMIService* service = MMIService::getInstance();
	//service->start();

	MMIManager::start();
}

void MMIManager::connectWiiMote() {
	trace("begin connectWiiMote()");

	WiiMote* wiiMote = new WiiMote(
			new WiiEventPoster(),
			WiiMote::REPORT_ALL);

	try {
		wiiMote->connect();
	} catch(...) {

	}
}

MMIManager::~MMIManager() {
	trace("begin Destructor()");

	if (_instance != NULL) {
		delete _instance;
		_instance = NULL;
	}
}

MMIManager* MMIManager::getInstance() {
	if (_instance == NULL) {
		_instance = new MMIManager();
	}
	return _instance;
}

void MMIManager::release() {
	running = false;
	if (eventBuffer != NULL) {
		eventBuffer->wakeUp();
	}

	lock();
	notifying = true;
	TRACE(logger, "release");

	if (eventBuffer != NULL) {
		delete eventBuffer;
		eventBuffer = NULL;
	}
	unlock();

	// Libera tudo relacionado a eventos multimodais.
	pthread_mutex_lock(&eventListenerMutex);

	if (eventListeners != NULL) {
		eventListeners->clear();
		delete eventListeners;
		eventListeners = NULL;
	}

	pthread_mutex_lock(&actMultimodalMutex);
	if (actionsToMultimodalListeners != NULL) {
		actionsToMultimodalListeners->clear();
		delete actionsToMultimodalListeners;
		actionsToMultimodalListeners = NULL;
	}
	pthread_mutex_unlock(&actMultimodalMutex);
	pthread_mutex_destroy(&actMultimodalMutex);

	pthread_mutex_lock(&devicesMutex);
	if (devices != NULL) {
		devices->clear();
		delete devices;
		devices = NULL;
	}
	pthread_mutex_unlock(&devicesMutex);
	pthread_mutex_destroy(&devicesMutex);

	pthread_mutex_unlock(&eventListenerMutex);
	pthread_mutex_destroy(&eventListenerMutex);
}

//*Métodos da Interface que será utilizada pelos DeviceComm
void MMIManager::postEvent(MMIEvent* event) {
	trace("begin postEvent(MMIEvent* )");

	if (event != NULL) {
		eventBuffer->postEvent(event);
	}
}

void MMIManager::postXMLEvent(XMLData* data) {
	trace("postXMLEvent(XMLData* ");

	MMIEvent* event = eventParser->ParseXMLEvent(data);
	postEvent(event);
}

void MMIManager::registerDevice(IDeviceComm* device, string deviceId) {
	trace("begin registerDevice(DeviceComm*, string)");

	pthread_mutex_lock(&devicesMutex);
	map<string, IDeviceComm*>::iterator it;
	it = devices->find(deviceId);
	if (it != devices->end()) {
		devices->insert(pair<string,IDeviceComm*>(deviceId, device));
		pthread_mutex_unlock(&devicesMutex);
	} else {
		pthread_mutex_unlock(&devicesMutex);
		throw IllegalParameterException("MMIManager::registerDevice.\n"
				"DeviceID already registered.",
				"br::ufscar::lince::mmi::MMIManager",
				"registerDevice(IDeviceComm*, string");
	}
}

void MMIManager::unregisterDevice(string deviceId) {
	trace("begin unregisterDevice(string )");

	pthread_mutex_lock(&devicesMutex);
	map<string, IDeviceComm*>::iterator it;
	it = devices->find(deviceId);
	if (it != devices->end()) {
		devices->erase(it);
		pthread_mutex_unlock(&devicesMutex);
	} else {
		pthread_mutex_unlock(&devicesMutex);
		throw IllegalParameterException("MMIManager::unregisterDevice.\n"
				"Wrong DeviceId informed.",
				"br::ufscar::lince::mmi::MMIManager",
				"unregisterDevice(string)");
	}
}

//Métodos da Interface que será utilizada pelas Aplicações
void MMIManager::addEventListener(MMIEventListener* listener,
		set<string>* eventTypes) {

	trace("addEventListener(MMIEventListener*, set<string>*)");
	if (!running) {
		return;
	}

	set<string>* nEventTypes = new set<string>();
	set<string>::iterator it = eventTypes->begin();
	while (it != eventTypes->end()) {
		nEventTypes->insert(*it);
		it++;
	}

	if (notifying) {
		pthread_mutex_lock(&actMultimodalMutex);
		LockedMultimodalAction* action;
		action = new LockedMultimodalAction;
		action->l      = listener;
		action->eventTypes = nEventTypes;
		action->isAdd  = true;

		actionsToMultimodalListeners->push_back(action);
		pthread_mutex_unlock(&actMultimodalMutex);
	} else {
		pthread_mutex_lock(&eventListenerMutex);
		performMultimodalInputLockedActions();

		map<MMIEventListener*, set<string>*>::iterator i;
		i = eventListeners->find(listener);
		if (i != eventListeners->end()) {
			pthread_mutex_unlock(&eventListenerMutex);
			delete nEventTypes;
			throw IllegalParameterException("MMIManager::addEventListener.\n"
									"Listener already registered.",
									"br::ufscar::lince::mmi::MMIManager",
									"addEventListener");
		} else {
			eventListeners->insert(pair<MMIEventListener*,set<string>*>(
					listener, nEventTypes));
		}
		pthread_mutex_unlock(&eventListenerMutex);
	}
}

void MMIManager::removeEventListener(MMIEventListener* listener) {
	trace("begin removeEventListener(MMIEventListener* )");
	if (!running) {
		return;
	}

	if (notifying) {
		pthread_mutex_lock(&actMultimodalMutex);
		LockedMultimodalAction* action;
		action = new LockedMultimodalAction;
		action->l      = listener;
		action->isAdd  = false;
		actionsToMultimodalListeners->push_back(action);
		pthread_mutex_unlock(&actMultimodalMutex);

	} else {
		pthread_mutex_lock(&eventListenerMutex);
		performMultimodalInputLockedActions();

		map<MMIEventListener*, set<string>*>::iterator it;
		it = eventListeners->find(listener);

		if (it != eventListeners->end()) {
			delete it->second;
			eventListeners->erase(it);
			pthread_mutex_unlock(&eventListenerMutex);
		} else {
			pthread_mutex_unlock(&eventListenerMutex);
			throw IllegalParameterException("MMIManager::removeEventListener.\n"
									"Listener isn't informed before.",
									"br::ufscar::lince::mmi::MMIManager",
									"removeEventListener(MMIEventListener* )");
		}

	}
}

vector<string>* MMIManager::getDevicesName() {
	trace("begin getDevicesName()");

	vector<string>* names = new vector<string>();
	map<string, IDeviceComm*>::iterator it;
	pthread_mutex_lock(&devicesMutex);
	it = devices->begin();
	while (it != devices->end()) {
		names->push_back(it->first);
		it++;
	}
	pthread_mutex_unlock(&devicesMutex);
	return names;
}

void MMIManager::callDeviceService(string deviceId, vector<string>* args) {
	trace("begin cllDeviceService(string, vector<string>*");

	map<string, IDeviceComm*>::iterator it;
	pthread_mutex_lock(&devicesMutex);
	it = devices->find(deviceId);
	if (it != devices->end()) {
		IDeviceComm* device = it->second;
		device->sendToDevice(args);
		pthread_mutex_unlock(&devicesMutex);
	} else {
		pthread_mutex_unlock(&devicesMutex);
		throw IllegalParameterException("MMIManager::removeEventListener.\n"
						"Listener informed isn't listen.",
						"br::ufscar::lince::mmi::MMIManager",
						"callDeviceService(string, vector<string>* )");
	}
}

void MMIManager::waitForUnlockCondition() {
	Thread::waitForUnlockCondition();
}

void MMIManager::run() {
	trace("begin run()");

	timeStamp = Functions::getCurrentTimeMillis();

	while (running && eventBuffer != NULL) {
		MMIEvent* event;

		eventBuffer->waitEvent();
		if (!running) {
			break;
		}

		event = eventBuffer->getNextEvent();
		while (event != NULL) {
			if ((Functions::getCurrentTimeMillis() -
					timeStamp) >= intervalTime) {

				timeStamp = Functions::getCurrentTimeMillis();

				if (!dispatchEvent(event)) {
					delete event;
					event = eventBuffer->getNextEvent();
					continue;
				}
			}

			event = eventBuffer->getNextEvent();
		}

	}
}

bool MMIManager::dispatchEvent(MMIEvent* event) {
	trace("begin dispatchEvent(MMIEvent* )");

	map<MMIEventListener*, set<string>*>::iterator i;

	if (!running) {
		return false;
	}

	notifying = true;
	pthread_mutex_lock(&eventListenerMutex);

	performMultimodalInputLockedActions();

	if (eventListeners->empty() || eventListeners == NULL) {
		pthread_mutex_unlock(&eventListenerMutex);
		notifying = false;
		return true;
	}

	i = eventListeners->begin();
	while (i != eventListeners->end()) {
		MMIEventListener* listener = i->first;
		set<string>* eventTypes = i->second;
		if (eventTypes != NULL && listener != NULL) {
			if (eventTypes->count(event->getEventType()) >= 1) {
				INFO(logger, "dispatchEvent - Vamos enviar o "
						"evento para o listener");
				bool result = listener->receiveEvent(event);
				INFO(logger, "dispatchEvent - evento enviado pelo listener.");
				if (!result) {
					pthread_mutex_unlock(&eventListenerMutex);
					notifying = false;
					return false;
				}
			}
		}
		++i;
	}
	pthread_mutex_unlock(&eventListenerMutex);
	notifying = false;
	return true;
}

void MMIManager::performMultimodalInputLockedActions() {
	LockedMultimodalAction* action;
	MMIEventListener* listener;

	map<MMIEventListener*, set<string>*>::iterator i;
	vector<LockedMultimodalAction*>::iterator j;

	if (!running) {
		return;
	}

	pthread_mutex_lock(&actMultimodalMutex);
	j = actionsToMultimodalListeners->begin();
	while (j != actionsToMultimodalListeners->end()) {
		action = *j;
		listener = action->l;

		if (action->isAdd) {
			i = eventListeners->find(listener);
			if (i != eventListeners->end()) {
				//#TODO: inventar forma de disparar as exeções avisando que não podia aicionar
			} else {
				eventListeners->insert(pair<MMIEventListener*,set<string>*>(
						listener, action->eventTypes));
			}
		} else {
			i = eventListeners->find(listener);
			if (i != eventListeners->end()) {
				delete i->second;
				eventListeners->erase(i);
			} else {
				//#TODO: inventar forma de disparar as exeções avisando que não podia remover
			}
		}

		delete action;
		++j;
	}

	actionsToMultimodalListeners->clear();
	pthread_mutex_unlock(&actMultimodalMutex);
}

}
}
}
}
