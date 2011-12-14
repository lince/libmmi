/*
 * ButtonEvent.cpp
 *
 *  Created on: Sep 28, 2010
 *      Author: caioviel
 */

#include "../include/KeyEvent.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/SAXException.hpp>
XERCES_CPP_NAMESPACE_USE

#include <libcpputil/NotImplementedException.h>
using namespace cpputil;

using namespace std;

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

KeyEvent::KeyEvent(string deviceId, string buttonId) :
		MMIEvent(deviceId, "key"),
		cpputil::logger::Loggable("br::ufscar::lince::mmi::KeyEvent") {

	trace("begin Constructor");
	this->keyId = buttonId;
}

KeyEvent::~KeyEvent() {
	trace("begin Destructor");
	// TODO Auto-generated destructor stub
}

KeyEvent::KeyEvent() :
			MMIEvent("", "key"), Parsable(),
			cpputil::logger::Loggable("br::ufscar::lince::mmi::KeyEvent"){

	trace("begin Internal Constructor");
}

void KeyEvent::parseXMLData(XMLData* data) {
	trace("begin parseXMLData(XMLData* )");

	deviceId = data->deviceId;

	DOMElement* e = data->element;

	DOMNodeList* children = e->getChildNodes();

		for (int i = 0; i < children->getLength(); i++) {
			DOMNode* currentNodeRoot = children->item(i);

			if (currentNodeRoot->getNodeType() == DOMNode::ELEMENT_NODE) {
				DOMElement* bodyName = dynamic_cast<xercesc::DOMElement*>(currentNodeRoot);

				if (XMLString::equals(bodyName->getTagName(),
						XMLString::transcode("body"))) {

					debug("Element body had been found.");

					DOMNodeList* bodyChildrens = bodyName->getChildNodes();
					const XMLSize_t nodeCount = bodyChildrens->getLength();

					for (XMLSize_t i = 0; i < nodeCount; i++) {
						DOMNode* currentNode = bodyChildrens->item(i);

						if (currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
							DOMElement* currentElement
									= dynamic_cast<xercesc::DOMElement*>(currentNode);

							if (XMLString::equals(currentElement->getTagName(),
									XMLString::transcode("key"))) {

								DOMNode* node = currentElement->getFirstChild();

								if (node && node->getNodeType() == DOMNode::TEXT_NODE) {
										DOMText* text = dynamic_cast<xercesc::DOMText*>(node);
										this->keyId =
												XMLString::transcode(text->getData());

										debug("KeyId: " + keyId);
										break;
								} else {
									//TODO: throw exception
								}

							} else {
								error((string) "Unexpected tag: " +
										XMLString::transcode(currentElement->getTagName()));
										//TODO: throw exception
							}
						} else {
							warning("It isn't a <Element>");
						}
					}
					break;
				} else {
					error((string) "Unexpected tag:  " +
							XMLString::transcode(bodyName->getTagName()));
					//TODO: throw Exception
				}
			}
		}
		trace("end parserHead(XMLData* )");

}

void KeyEvent::parseJson(string jsonString) {
	trace("parseJson(string)");
	throw cpputil::NotImplementedException(
			"This functionality has been not implemented yet",
			"br::ufscar::lince::mmi::KeyEvent",
			"parseJson(string)");

}

string KeyEvent::getKeyId() {
	return keyId;
}

}
}
}
}
