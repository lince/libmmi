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

#include <cpputil/NotImplementedException.h>

namespace br{
namespace ufscar{
namespace lince{
namespace mmi {

KeyEvent::KeyEvent(string deviceId, string buttonId) :
		MMIEvent(deviceId, "key"){

	logger = Logger::getInstance();
	logger->registerClass(this, "br::ufscar::lince::mmi::KeyEvent");

	TRACE(logger, "Construtor - Padrão");

	this->keyId = buttonId;
}

KeyEvent::~KeyEvent() {
	// TODO Auto-generated destructor stub
}

KeyEvent::KeyEvent() :
	MMIEvent("", "key"), Parsable(){

	logger = Logger::getInstance();
	logger->registerClass(this, "br::ufscar::lince::mmi::KeyEvent");

	TRACE(logger, "Construtor - Interno XML");
}

void KeyEvent::parseXMLData(XMLData* data) {
	TRACE(logger, "parseXMLData");

	deviceId = data->deviceId;

	DOMElement* e = data->element;

	DOMNodeList* children = e->getChildNodes();

		for (int i = 0; i < children->getLength(); i++) {
			DOMNode* currentNodeRoot = children->item(i);

			if (currentNodeRoot->getNodeType() == DOMNode::ELEMENT_NODE) {
				DOMElement* bodyName = dynamic_cast<xercesc::DOMElement*>(currentNodeRoot);

				if (XMLString::equals(bodyName->getTagName(),
						XMLString::transcode("body"))) {

					DEBUG(logger, "encontrado elemento body. Iniciando parse.");

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

										INFO(logger, "Valor Encontrado: " + keyId);
										break;
								} else {
									//TODO: throw exception
								}

							} else {
								INFO(logger, (string) "ERRO! Tag inesperada: " +
										XMLString::transcode(currentElement->getTagName()));
										//TODO: throw exception
							}
						} else {
							INFO(logger, "Não é elemento");
						}
					}
					break;
				} else {
					INFO(logger, (string) "ERRO! Tag inesperada: " +
							XMLString::transcode(bodyName->getTagName()));
					//TODO: throw Exception
				}
			}
		}
		TRACE(logger, "saindo do parserHead()");

}

void KeyEvent::parseJson(string jsonString) {
	TRACE(logger, "parseJson(string)");
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
