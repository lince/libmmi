/*
 * ButtonEvent.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/HoldOnEvent.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/SAXException.hpp>
XERCES_CPP_NAMESPACE_USE

#include <libjson/libjson.h>

#include <libcpputil/NotImplementedException.h>
using namespace std;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

HoldOnEvent::HoldOnEvent(string deviceId, HoldOnEventType type) :
		MMIEvent(deviceId, "key"),
		cpputil::logger::Loggable("br::ufscar::lince::mmi::HoldOnEvent") {

	trace("begin Constructor");

	this->type = type;
	this->timestamp = "";
}

HoldOnEvent::~HoldOnEvent() {
	trace("begin Destructor");
}

HoldOnEvent::HoldOnEvent() :
			MMIEvent("", "key"), Parsable(),
			cpputil::logger::Loggable("br::ufscar::lince::mmi::HoldOnEvent") {

	trace("begin Constructor");
	this->type = HoldOnEvent::NONE;
	this->timestamp = "";
}


HoldOnEvent::HoldOnEventType HoldOnEvent::getHoldOnEventType() {
	return this->type;
}


string HoldOnEvent::getTimestamp() {
	return timestamp;
}


void HoldOnEvent::setTimestamp(string timeStamp) {
	this->timestamp = timestamp;
}


void HoldOnEvent::parseXMLData(XMLData* data) {
	trace(" begin parseXMLData(XMLData*)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::KeyEvent"
			"parseXMLData(XMLData*)");

}

void HoldOnEvent::parseJson(string jsonString) {
	trace("begin parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::KeyEvent"
			"parseJson(string)");

	/*char *json = "{ "
			"\"multimodal\" : {"
			"\"device\" : {"
			"\"id\" : \"DEADBEEF-DEAF-BABA-FEED-BABE00000006\","
			"\"model\" : \"iPhone 3GS\","
			"},"
			"\userId\" : \"nomeusuario\","
			"\"events\" : ["
			"{"
			"\"type\" : \"holdon\", "
				"\"timestamp\" : \"1504\", "
				"\"command\" : \"goBack\""
			"} "
			"] } }";

	INFO(logger, json);

	JSONNODE *n = json_parse(json);
	if (n == NULL){
		printf("Invalid JSON Node\n");
		return;
	}

	JSONNODE_ITERATOR i = json_begin(n);
	while (i != json_end(n)){
		if (*i == NULL){
			printf("Invalid JSON Node\n");
			return;
		}

		// recursively call ourselves to dig deeper into the tree
		if (json_type(*i) == JSON_ARRAY || json_type(*i) == JSON_NODE){
			ParseJSON(*i);
		}

		// get the node name and value as a string
		json_char *node_name = json_name(*i);

		// find out where to store the values
		if (strcmp(node_name, "RootA") == 0){
			json_char *node_value = json_as_string(*i);
			strcpy(rootA, node_value);
			json_free(node_value);
		}
		else if (strcmp(node_name, "ChildA") == 0){
			json_char *node_value = json_as_string(*i);
			strcpy(childA, node_value);
			json_free(node_value);
		}
		else if (strcmp(node_name, "ChildB") == 0)
			childB = json_as_int(*i);

		// cleanup and increment the iterator
		json_free(node_name);
		++i;
	}
	json_delete(n);*/
}



}
}
}
}
