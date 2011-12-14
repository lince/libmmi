/*
 * AccelerationEvent.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/AccelerationEvent.h"

#include <libcpputil/NotImplementedException.h>
using namespace cpputil::logger;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi{


AccelerationEvent::AccelerationEvent(string deviceId,
		int xValue, int yValue, int zValue) : MMIEvent(deviceId, "acceleration"),
		Loggable("br::ufscar::lince::mmi::AccelerationEvent") {

	trace("begin Constructor");

	this->xValue = xValue;
	this->yValue = yValue;
	this->zValue = zValue;
}

AccelerationEvent::AccelerationEvent() : MMIEvent("", "acceleration"),
		Parsable(), Loggable("br::ufscar::lince::mmi::AccelerationEvent") {


	trace("begin default constructor");

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
	trace("begin parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::AccelerationEvent",
			"parseXMLData(XMLData*)");
}

void AccelerationEvent::parseJson(string jsonString) {
	trace("begin parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::AccelerationEvent",
			"parseJson(string)");
}

}
}
}
}
