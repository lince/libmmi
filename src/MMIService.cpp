#include "../include/MMIService.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

#include "../include/MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

namespace br {
    namespace ufscar {
        namespace lince {
            namespace mmi {
                namespace upnp {

                        MMIService* MMIService::_instance = NULL;
                        const char* MMIService::UUID_PATH = ".mmiservice.uuid";
                        const char* MMIService::DEVICE_TYPE = "urn:schemas-upnp-org:device:MMIDevice:1";
                        const char* MMIService::DEVICE_DESCRIPTION =
                                "<?xml version=\"1.0\" ?>\n"
                                "<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
                                " 	<specVersion>\n"
                                " 		<major>1</major>\n"
                                " 		<minor>0</minor>\n"
                                " 	</specVersion>\n"
                                " 	<device>\n"
                                " 		<deviceType>urn:schemas-upnp-org:device:MMIDevice:1</deviceType>\n"
                                " 		<friendlyName>MMI Service</friendlyName>\n"
                                " 		<manufacturer>Lince</manufacturer>\n"
                                " 		<manufacturerURL>http://lince.dc.ufscar.br</manufacturerURL>\n"
                                " 		<modelDescription>Serviço MMI - UPnP</modelDescription>\n"
                                " 		<modelName>MMIServiceApp</modelName>\n"
                                " 		<modelNumber>1.0</modelNumber>\n"
                                " 		<modelURL>http://lince.dc.ufscar.br</modelURL>\n"
                                " 		<serviceList>\n"
                                " 			<service>\n"
                                " 				<serviceType>urn:schemas-upnp-org:service:MMIService:1</serviceType>\n"
                                " 				<serviceId>urn:schemas-upnp-org:serviceId:MMIService:1</serviceId>\n"
                                " 				<SCPDURL>/service/mmiservice/description.xml</SCPDURL>\n"
                                " 				<controlURL>/service/mmiservice/control</controlURL>\n"
                                " 				<eventSubURL>/service/mmiservice/eventSub</eventSubURL>\n"
                                " 			</service>\n"
                                " 		</serviceList>\n"
                                "	</device>\n"
                                "</root>\n";
                        const char* MMIService::SERVICE_TYPE = "urn:schemas-upnp-org:service:MMIService:1";
                        const char* MMIService::SERVICE_DESCRIPTION =
                                "<?xml version=\"1.0\"?>\n"
                                "<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\" >\n"
                                " 	<specVersion>\n"
                                " 		<major>1</major>\n"
                                " 		<minor>0</minor>\n"
                                " 	</specVersion>\n"
                                " 	<actionList>\n"
                                " 		<action>\n"
                                " 			<name>PostEvent</name>\n"
                                " 			<argumentList>\n"
                                " 				<argument>\n"
                                " 					<name>Event</name>\n"
                                " 					<relatedStateVariable>CurrentEvent</relatedStateVariable>\n"
                                " 					<direction>in</direction>\n"
                                " 				</argument>\n"
                                " 				<argument>\n"
                                " 					<name>Result</name>\n"
                                " 					<relatedStateVariable>CurrentResult</relatedStateVariable>\n"
                                " 					<direction>out</direction>\n"
                                " 				</argument>\n"
                                " 			</argumentList>\n"
                                " 		</action>\n"
                                " 	</actionList>\n"
                                " 	<serviceStateTable>\n"
                                " 		<stateVariable sendEvents=\"no\">\n"
                                " 			<name>CurrentEvent</name>\n"
                                " 			<dataType>string</dataType>\n"
                                " 		</stateVariable>\n"
                                " 		<stateVariable sendEvents=\"no\">\n"
                                " 			<name>CurrentResult</name>\n"
                                " 			<dataType>boolean</dataType>\n"
                                " 		</stateVariable>\n"
                                " 	</serviceStateTable>\n"
                                "</scpd>\n";

                        MMIService::MMIService() : UPnPDevice() {
                            logger = LoggerUtil::getLogger("br.ufscar.lince.ginga.mmi.upnp.mmiservice");
                            LoggerUtil_info(logger, "Entrando no construtor MMIService()!");

                            restoreUUID(string(Utils::getHomeDir()).append("/").append(UUID_PATH).c_str());

                            if (loadDescription(DEVICE_DESCRIPTION) == false)
                                throw "Invalid description!";

                            UPnPService* serv = getService();

                            bool ret = serv->loadSCPD(SERVICE_DESCRIPTION);
                            if (ret == false)
                                throw "Invalid description";

                            serv->setUPnPActionListener(this);
                            serv->setUPnPQueryListener(this);

                            initializeUPnPStateVariables();

                            LoggerUtil_info(logger, "Saindo do construtor MMIService()!");
                        }

                        MMIService::~MMIService() {
                            stop();
                        }

                        MMIService* MMIService::getInstance() {
                            if (_instance == NULL) {
                                _instance = new MMIService();
                            }
                            return _instance;
                        }

                        bool MMIService::start() {
                            bool result = UPnPDevice::start();
                            // tarefas adicionais, caso necessário
                            return result;
                        }

                        bool MMIService::stop() {
                            return UPnPDevice::stop();
                        }

                        void MMIService::initializeUPnPStateVariables() {
                            getService()->getUPnPStateVariable("CurrentEvent")->setValue("");
                        }

                        UPnPService* MMIService::getService() {
                            return this->getUPnPService(SERVICE_TYPE);
                        }

                        bool MMIService::actionRequest(UPnPAction *action) {
                            string actionName = action->getName();

                            if (actionName.compare("PostEvent") == 0)
                                return actionPostEvent(action);

                            return false;
                        }

                        bool MMIService::variableRequest(UPnPStateVariable *stateVar) {
                            UPnPStateVariable* serviceStateVar = getService()->getUPnPStateVariable(stateVar->getName());
                            if (serviceStateVar == NULL)
                                return false;

                            stateVar->setValue(serviceStateVar->getValue());

                            return true;
                        }

                        bool MMIService::actionPostEvent(UPnPAction *action) {
                            LoggerUtil_info(logger, "Entrando no metodo actionPostEvent(...)!");

                            string xml = action->getUPnPArgument("Event")->getValue();

                            getService()->getUPnPStateVariable("CurrentEvent")->setValue(xml.c_str());

                            MMIManager* eim = MMIManager::getInstance();
                            XMLData* xmlData = new XMLData();
                            xmlData->payload = (char*) xml.c_str();
                            xmlData->length = xml.length();
                            eim->postXMLEvent(xmlData);

                            LoggerUtil_debug(logger, "XML recebido: " << xml.c_str());

                            action->getUPnPArgument("Result")->setValue("1");

                            return true;
                        }

                }
            }
        }
    }
}
