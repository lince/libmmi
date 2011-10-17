#include "../include/EventParser.h"

#include "../include/AccelerationFactory.h"
#include "../include/KeyEventFactory.h"

//#include "cm/IComponentManager.h"
//using namespace ::br::pucrio::telemidia::ginga::core::cm;

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/sax/SAXException.hpp>
XERCES_CPP_NAMESPACE_USE

namespace br {
namespace ufscar {
namespace lince {
namespace mmi {

EventParser* EventParser::_instance = NULL;

EventParser::EventParser() {
	logger = Logger::getInstance();

	logger->registerClass(this, (string) "br::ufscar::lince::mmi::EventParser");

	TRACE(logger, "Constructor");

	XMLPlatformUtils::Initialize();
}

EventParser::~EventParser() {
	TRACE(logger, "Destructor");

	XMLPlatformUtils::Terminate();
}

MMIEvent* EventParser::ParseXMLEvent(XMLData* data) {
	TRACE(logger, "ParseXMLEvent(XMLDdata* )");

	bool bFailed = false;

	// create new parser instance.
	XercesDOMParser *parser = new XercesDOMParser();
	if (!parser) {
			INFO(logger, "não foi possível criar um parser");
			return NULL;
	} else {
		try {
			string aux = data->payload;
			//checking if source is data->payload or uri
			if (aux.find("<") != std::string::npos) {
				DEBUG(logger, "MemBufInputSource");
				MemBufInputSource xmlSource(
						(XMLByte*)(data->payload),
						data->length,
						XMLString::transcode("xmlContent"));

				parser->parse(xmlSource);

			} else {
				DEBUG(logger, "LocalFileInputSource");
				LocalFileInputSource source(
						XMLString::transcode(data->payload));

				parser->parse(source);
			}

			bFailed = parser->getErrorCount() != 0;
			if (bFailed) {
				int status, errnum;
				XMLSSize_t lineError, colError;
				XMLCh *segundo, *format, *systemId, *publicId;

				cerr << "Parsing " << data->payload <<std::endl;
				cerr << " error count: ";
				cerr << parser->getErrorCount() << std::endl;

				parser->error(status, segundo,
						(XMLErrorReporter::ErrTypes)errnum,
						format, systemId, publicId, lineError, colError);

				cerr<<"status: "<<status<<endl;
				//cerr<<XMLString::transcode(segundo)<<endl;
				cerr<<errnum<<endl;
				cerr<<XMLString::transcode(format)<<endl;
				cerr<<XMLString::transcode(systemId)<<endl;
				cerr<<XMLString::transcode(publicId)<<endl;
				cerr<<"line: "<<lineError<<" column:"<<colError<<endl<<endl;
			}

		} catch (const DOMException& e) {
			cerr << "DOM Exception parsing ";
			cerr << data->payload;
			cerr << " reports: ";

			// was message provided?
			if (e.msg) {
				// yes: display it as ascii.
				char *strMsg = XMLString::transcode(e.msg);
				cerr << strMsg << std::endl;
				XMLString::release(&strMsg);

			} else {
				// no: just display the error code.
				cerr << e.code << std::endl;
			}

			bFailed = true;

		} catch (const XMLException& e) {
			cerr << "data->payload Exception parsing ";
			cerr << data->payload;
			cerr << " reports: ";
			cerr << e.getMessage() << std::endl;
			bFailed = true;

		} catch (const SAXException& e) {
			cerr << "SAX Exception parsing ";
			cerr << data->payload;
			cerr << " reports: ";
			cerr << e.getMessage() << std::endl;
			bFailed = true;

		} catch (...) {
			cerr << "An exception parsing ";
			cerr << data->payload << std::endl;
			bFailed = true;
		}

		// did the input document parse okay?
		if (!bFailed) {
			DOMDocument *pDoc = parser->getDocument();
			DOMElement* elementRoot = pDoc->getDocumentElement();

			if (!elementRoot) {
				INFO(logger, "empty data->payload document");
	//			throw(std::runtime_error("empty data->payload document"));
			}

			data->element = elementRoot;

			parseHead(data);

			EventFactory* factory = getFactoryByType(
					data->eventType);

			if (factory != NULL) {
				return factory->CreateEvent(data);
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
	TRACE(logger, "getFacotoryByType(string)");

	if (type == "acceleration") {
		return new AccelerationFactory();
	} else if (type == "key" ) {
		return new KeyEventFactory();
	}
	return NULL;
}

void EventParser::parseHead(XMLData* data) {
	TRACE(logger, "parseHead(XMLData* )");

	DOMElement* e = data->element;

	if (XMLString::equals(e->getTagName(),
			XMLString::transcode("multimodal"))) {

		const XMLCh* id = e->getAttribute(XMLString::transcode("id"));
		DEBUG(logger, (string) "eventId: " + XMLString::transcode(id) );
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

				DEBUG(logger, "encontrado elemento head. Iniciando parse.");

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

							DEBUG(logger, "Encontrou a tag eventType");

							const XMLCh* attribute = currentElement->getAttribute(
									XMLString::transcode("id"));

							data->eventType = XMLString::transcode(attribute);

						} else {
							DEBUG(logger, (string) "ERRO! Tag inesperada: " +
									XMLString::transcode(currentElement->getTagName()));
						}
					} else {
						DEBUG(logger, "Não é elemento");
					}
				}
				break;
			} else {
				DEBUG(logger, (string) "ERRO! Tag inesperada: " +
						XMLString::transcode(headElement->getTagName()));
				//TODO: throw Exception
			}
		}
	}
	TRACE(logger, "saindo do parserHead()");
}

}
}
}
}
