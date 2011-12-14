/*
 * AccelerationEvent.h
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#ifndef ACCELERATIONEVENT_H_
#define ACCELERATIONEVENT_H_

#include <string>

#include <libcpputil/logger/Logger.h>

#include "MMIEvent.h"
#include "Parsable.h"

namespace br{
namespace ufscar{
namespace lince{
namespace mmi{

/**
 * This class represent a Acceleration Multimodal Event.
 */
class AccelerationFactory;

class AccelerationEvent :
				public MMIEvent,
				public Parsable,
				public cpputil::logger::Loggable {
public:

	/**
	 * Construtor
	 * @param deviceId The id of the device that generate the acceleration event.
	 * @param xValue The acceleration value of X axis.
	 * @param yValue The acceleration value of Y axis.
	 * @param zValue The acceleration value of Z axis.
	 */
	AccelerationEvent(std::string deviceid, int xValue, int yValue, int zValue);

	/**
	 * Destructor
	 */
	virtual ~AccelerationEvent();

	/**
	 * This method return the acceleration value of X axis.
	 * @return X axis Acceleration value of this Acceleration Event.
	 */
	virtual int getXValue();

	/**
	 * This method return the acceleration value of Y axis.
	 * @return Y axis Acceleration value of this Acceleration Event.
	 */
	virtual int getYValue();

	/**
	 * This method return the acceleration value of Z axis.
	 * @return Z axis Acceleration value of this Acceleration Event.
	 */
	virtual int getZValue();

protected:
	AccelerationEvent();
	void parseXMLData(XMLData* data);
	void parseJson(std::string jsonString);

protected:
	int xValue;
	int yValue;
	int zValue;

friend class AccelerationFactory;
};

}
}
}
}

#endif /* ACCELERATIONEVENT_H_ */
