/*
 * MMIManager.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef MMIMANAGER_H_
#define MMIMANAGER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;


#include <cpputil/Functions.h>
#include <cpputil/IllegalParameterException.h>
#include <cpputil/Thread.h>
using namespace cpputil;

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include "MMIEvent.h"
#include "IDeviceComm.h"
#include "MMIEventListener.h"
#include "EventBuffer.h"
#include "EventParser.h"

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

typedef struct {
	::br::ufscar::lince::mmi::MMIEventListener* l;
	::std::set<string>* eventTypes;
	bool isAdd;
} LockedMultimodalAction;

/**
 * This class control the multimodal interactions.
 * The application must register themselves in the instance of MMIManager to receive the
 * MMIEvents that occurs.
 */
class MMIManager : public Thread, public Loggable {

public:
	/**
	 * This method allow getting the unique instance of MMIManager
	 * @param Unique instance of MMIManager.
	 */
	static MMIManager* getInstance();

	/**
	 * This method release the internal variabels of the MMIManager.
	 */
	virtual void release();

public:
	/**
	 * This method allow the application connects with a wiimote device.
	 */
	void connectWiiMote();

	/**
	 * This method allow a device driver post Multimodal events generateds.
	 * @param event The Multimodal event.
	 */
	void postEvent(MMIEvent* event);

	/**
	 * This method allow the network services post XML Documents that represents a Multimodal Event.
	 * The XML Documents will be parsed and reposted as a instance of MMIEvent.
	 * @param event The XML Document Representation.
	 */
	void postXMLEvent(XMLData* event);

	/**
	 * This method allows devices register themselves in the MMIManager.
	 * @param device The Device instance representation.
	 * @param deviceId The identification of the device.
	 */
	void registerDevice(IDeviceComm* device, string deviceId);

	/**
	 * This method allow devices unregister.
	 * @param deviceId The deviceId that will be unregistred.
	 */
	void unregisterDevice(string deviceId);

	/**
	 * This method allow the registration of objects that wish receive multimodal events.
	 * @param The instance of object that wish receive multimodal events
	 * @param eventTypes a set of eventTypes that the object wish receive.
	 */
	void addEventListener(MMIEventListener* listener, set<string>* eventTypes);

	/**
	 * This method remove objets of the list of multimodal event listeners.
	 * @param listener The object that will be removed of the list.
	 */
	void removeEventListener(MMIEventListener* listener);

	/**
	 * This method returns the id of all devices registred.
	 * @param A Vector with the id of all devices.
	 */
	vector<string>* getDevicesName();

	/**
	 * This method allow applications send message to devices.
	 * @param deviceId The deviceId that will receive the message.
	 * @param args A vector with the message that will be send.
	 */
	void callDeviceService(string deviceId, vector<string>* args);

	virtual void waitForUnlockCondition();
private:
	static MMIManager* _instance;

	Logger* logger;

	map<MMIEventListener*, set<string>*>* eventListeners;

	map<string, IDeviceComm*>* devices;

	vector<LockedMultimodalAction*>* actionsToMultimodalListeners;

	pthread_mutex_t eventListenerMutex;

	pthread_mutex_t devicesMutex;

	pthread_mutex_t actMultimodalMutex;

	bool running;

	bool notifying;

	EventBuffer* eventBuffer;

	EventParser* eventParser;

	double timeStamp;

	double intervalTime;


private:
	MMIManager();

	void run();

	bool dispatchEvent(MMIEvent* event);

	void performMultimodalInputLockedActions();

	virtual ~MMIManager();
};

}
}
}
}

#endif /* MMIMANAGER_H_ */
