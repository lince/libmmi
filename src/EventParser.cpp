#include "../include/EventParser.h"

#include "../include/AccelerationFactory.h"
#include "../include/KeyEventFactory.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/sax/SAXException.hpp>
XERCES_CPP_NAMESPACE_USE

#include <sstream>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

EventParser* EventParser::_instance = NULL;

EventParser::EventParser()
		: cpputil::logger::Loggable("br::ufscar::lince::mmi::EventParser") {

	trace("begin Constructor");

	XMLPlatformUtils::Initialize();
}

EventParser::~EventParser() {
	trace("begin Destructor");

	XMLPlatformUtils::Terminate();
}

MMIEvent* EventParser::ParseXMLEvent(XMLData* data) {
	trace("begin parseXMLEvent(XMLDdata* )");

	bool bFailed = false;

	// create new parser instance.
	XercesDOMParser *parser = new XercesDOMParser();
	if (!parser) {
			info("Couldn't create a parser.");
			return NULL;
	} else {
		try {
			string aux = data->payload;
			//checking if source is data->payload or uri
			if (aux.find("<") != std::string::npos) {
				debug("Using MemBufInputSource");
				MemBufInputSource xmlSource(
						(XMLByte*)(data->payload),
						data->length,
						XMLString::transcode("xmlContent"));

				parser->parse(xmlSource);

			} else {
				debug("Using LocalFileInputSource");
				LocalFileInputSource source(
						XMLString::transcode(data->payload));

				parser->parse(source);
			}

			bFailed = parser->getErrorCount() != 0;
			if (bFailed) {
				int status, errnum;
				XMLSSize_t lineError, colError;
				XMLCh *segundo, *format, *systemId, *publicId;
				std::stringstream stream;

				stream << "Parsing " << data->payload <<std::endl;
				stream << " error count: ";
				stream << parser->getErrorCount() << std::endl;

				parser->error(status, segundo,
						(XMLErrorReporter::ErrTypes)errnum,
						format, systemId, publicId, lineError, colError);

				stream<<"status: "<<status<<endl;
				//stream<<XMLString::transcode(segundo)<<endl;
				stream<<errnum<<endl;
				stream<<XMLString::transcode(format)<<endl;
				stream<<XMLString::transcode(systemId)<<endl;
				stream<<XMLString::transcode(publicId)<<endl;
				stream<<"line: "<<lineError<<" column:"<<colError;
				error(stream.str());
			}

		} catch (const DOMException& e) {
			std::stringstream stream;
			stream << "DOM Exception parsing ";
			stream << data->payload;
			stream << " reports: ";

			// was message provided?
			if (e.msg) {
				// yes: display it as ascii.
				char *strMsg = XMLString::transcode(e.msg);
				cerr << strMsg << std::endl;
				XMLString::release(&strMsg);

			} else {
				// no: just display the error code.
				stream << e.code;
			}

			bFailed = true;
			error(stream.str());

		} catch (const XMLException& e) {
			std::stringstream stream;
			stream << "data->payload Exception parsing ";
			stream << data->payload;
			stream << " reports: ";
			stream << e.getMessage();
			error(stream.str());
			bFailed = true;

		} catch (const SAXException& e) {
			std::stringstream stream;
			stream << "SAX Exception parsing ";
			stream << data->payload;
			stream << " reports: ";
			stream << e.getMessage();
			error(stream.str());
			bFailed = true;

		} catch (...) {
			std::stringstream stream;
			stream << "An exception parsing ";
			stream << data->payload;
			error(stream.str());
			bFailed = true;

		}

		// did the input document parse okay?
		if (!bFailed) {
			DOMDocument *pDoc = parser->getDocument();
			DOMElement* elementRoot = pDoc->getDocumentElement();

			if (!elementRoot) {
				warning("empty data->payload document");
				//TODO: Throw XmlParserException
				throw(std::runtime_error("empty data->payload document"));
			}

			data->element = elementRoot;

			parseHead(data);

			EventFactory* factory = getFactoryByType(
					data->eventType);

			if (factory != NULL) {
				return factory->CreateEvent(data);
			} else {
				warning("The eventType '" + data->eventType + " doesn't have a EventFactory.");
				return NULL;
			}
		}
	}

	return NULL;
}

EventParser* EventParser::getInstance() {

	if (_instance == NULL) {
		_instance = new EventParser();
	}
	return _instance;
}

EventFactory* EventParser::getFactoryByType(string type) {
	trace("begin getFacotoryByType(string)");

	if (type == "acceleration") {
		return new AccelerationFactory();
	} else if (type == "key" ) {
		return new KeyEventFactory();
	}
	return NULL;
}

void EventParser::parseHead(XMLData* data) {
	trace("begin parseHead(XMLData* )");

	DOMElement* e = data->element;

	if (XMLString::equals(e->getTagName(),
			XMLString::transcode("multimodal"))) {

		const XMLCh* id = e->getAttribute(XMLString::transcode("id"));
		debug("eventId: " + XMLString::transcode(id) );
		data->eventId = XMLString::transcode(id);
	} else {
		return;
		//TODO: throw exception
	}

	// Acessa os filhos do elemento raíz e sua quantidade.
	DOMNodeList* children = e->getChildNodes();

	for (int i = 0; i < children->getLength(); i++) {
		DOMNode* currentNodeRoot = children->item(i);

		if (currentNodeRoot->getNodeType() == DOMNode::ELEMENT_NODE) {
			DOMElement* headElement = dynamic_cast<xercesc::DOMElement*>(currentNodeRoot);

			if (XMLString::equals(headElement->getTagName(),
					XMLString::transcode("head"))) {

				debug("Element <Head> had been found. Starting Parse.");

				DOMNodeList* childrenHead = headElement->getChildNodes();
				const XMLSize_t nodeCount = childrenHead->getLength();

				for (XMLSize_t i = 0; i < nodeCount; i++) {
					DOMNode* currentNode = childrenHead->item(i);

					if (currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
						DOMElement* currentElement
								= dynamic_cast<xercesc::DOMElement*>(currentNode);

						if (XMLString::equals(currentElement->getTagName(),
								XMLString::transcode("device"))) {

							const XMLCh* attribute = currentElement->getAttribute(
									XMLString::transcode("id"));

							data->deviceId = XMLString::transcode(attribute);

							attribute = currentElement->getAttribute(
									XMLString::transcode("model"));

							data->deviceModel =  XMLString::transcode(attribute);

						} else if (XMLString::equals(currentElement->getTagName(),
								XMLString::transcode("eventType"))) {

							debug("Attribute eventType had been found");

							const XMLCh* attribute = currentElement->getAttribute(
									XMLString::transcode("id"));

							data->eventType = XMLString::transcode(attribute);

						} else {
							error("Unexpected Tag: " +
									XMLString::transcode(currentElement->getTagName()));
							//TODO: Throw Exception
						}
					} else {
						debug("It isn't a element.");
					}
				}
				break;
			} else {
				error("Unexpected Tag: " +
						XMLString::transcode(headElement->getTagName()));
				//TODO: throw Exception
			}
		}
	}
	trace("end parserHead()");
}

}
}
}
}
