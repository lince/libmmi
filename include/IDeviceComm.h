/*
 * IDeviceConn.h
 *
 *  Created on: Sep 24, 2010
 *      Author: caioviel
 */

#ifndef IDEVICECOMM_H_
#define IDEVICECOMM_H_

#include <string>
#include <vector>

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

/**
 * This abstract class represents a device that can generate multimodal events.
 */
class IDeviceComm {

public:
	/**
	 * This method stabilishes a connect between the device and the MMIManager, allowing
	 * the device reports his multimodal events.
	 */
	virtual void connect() = 0;

	/**
	 * This method finishes the connection between the devica and MMIManager.
	 */
	virtual void disconnect() = 0;

	/**
	 * This method allows send a message to the device.
	 * @param args A array of strings that will contain the message.
	 */
	virtual void sendToDevice(std::vector<std::string>* args) = 0;

	/**
	 * This method return the id of the device.
	 * @return Device identification.
	 */
	virtual std::string getDeviceId() = 0;

	/**
	 * This method make the device reset its internals variables.
	 */
	virtual void release() = 0;

protected:
	/**
	 * Generic Destructor
	 */
	virtual ~IDeviceComm() {};
};

}
}
}
}


#endif /* IDEVICECOMM_H_ */
