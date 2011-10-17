/*
 * AccelerationEvent.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/AccelerationEvent.h"

#include <cpputil/NotImplementedException.h>

namespace br{
namespace ufscar{
namespace lince{
namespace mmi{


AccelerationEvent::AccelerationEvent(string deviceId,
		int xValue, int yValue, int zValue) : MMIEvent(deviceId, "acceleration") {

	logger = Logger::getInstance();
	logger->registerClass(this,
			"br::ufscar::lince::mmi::AccelerationEvent");

	TRACE(logger, "Constructor");

	this->xValue = xValue;
	this->yValue = yValue;
	this->zValue = zValue;
}

AccelerationEvent::AccelerationEvent() :
		MMIEvent("", "acceleration"), Parsable() {

	logger = Logger::getInstance();
	logger->registerClass(this,
			"br::ufscar::lince::mmi::AccelerationEvent");

	TRACE(logger, "Constructor");

	this->xValue = 0;
	this->yValue = 0;
	this->zValue = 0;
}

AccelerationEvent::~AccelerationEvent() {

}

int AccelerationEvent::getXValue() {
	return this->xValue;
}

int AccelerationEvent::getYValue() {
	return this->yValue;
}

int AccelerationEvent::getZValue() {
	return this->zValue;
}

void AccelerationEvent::parseXMLData(XMLData* data) {
	TRACE(logger, "parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::AccelerationEvent",
			"parseXMLData(XMLData*)");
}

void AccelerationEvent::parseJson(string jsonString) {
	TRACE(logger, "parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::AccelerationEvent",
			"parseJson(string)");
}

}
}
}
}
