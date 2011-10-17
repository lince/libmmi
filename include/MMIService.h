#ifndef _MMISERVICE_H
#define	_MMISERVICE_H

#include <string>
#include <hones/UPnPDevice.h>
#include <hones/UPnPActionListener.h>
#include <hones/UPnPQueryListener.h>
#include <hones/UPnPService.h>
#include <hones/UPnPAction.h>
#include <hones/UPnPArgument.h>
#include <hones/UPnPStateVariable.h>
#include <linceutil/LoggerUtil.h>
using namespace br::ufscar::lince::util;
using namespace std;
using namespace br::ufscar::lince::ginga::hones::upnp;

namespace br {
    namespace ufscar {
        namespace lince {
            namespace mmi {
                namespace upnp {

                        /**
                         * Esta classe representa um dispositivo e seu serviços.
                         * Cada dispositivo possui sua descrição e os serviços que disponibiliza.
                         * Recebe as chamadas de métodos (ações), faz o tratamento e devolve o
                         * resultado para o dispositivo que o invocou.
                         */

                        class MMIService : public UPnPDevice, public UPnPActionListener, public UPnPQueryListener {
                        private:
                            /** descrição (XML) do dispositivo e quais serviços possui */
                            static const char* DEVICE_DESCRIPTION;
                            /** string com a identificação do tipo do dispositivo */
                            static const char* DEVICE_TYPE;
                            /** string com a identificação do tipo do serviço */
                            static const char* SERVICE_TYPE;
                            /** string (XML) com a descrição das funcionalidades do serviço */
                            static const char* SERVICE_DESCRIPTION;
                            /** local para armazenamento do UUID, para evitar que um novo seja gerado a cada execução da aplicação */
                            static const char* UUID_PATH;
                            /** Instância única */
                            static MMIService* _instance;
                            HLoggerPtr logger;

                        protected:

                            /**
                             * Construtor.
                             */
                            MMIService();

                            /**
                             * Destrutor.
                             */
                            ~MMIService();

                        public:

                            /**
                            * Acessa a instância única.
                            */
                            static MMIService* getInstance();

                            /**
                             * Inicia os serviços.
                             * @return true, caso obtena sucesso na operação, ou false, caso contrário.
                             */
                            bool start();

                            /**
                             * Pára os serviços.
                             * @return true, caso obtena sucesso na operação, ou false, caso contrário.
                             */
                            bool stop();

                            /**
                             * Inicializa as variáveis de estado necessárias ao funcionamento do serviço.
                             */
                            void initializeUPnPStateVariables();

                            /**
                             * Retorna a instância do serviço UPnP.
                             * @return serviço MMIService.
                             */
                            UPnPService* getService();

                            /**
                             * Recebe solicitações de ações a serem executadas.
                             * @param action ação a ser executada.
                             * @return true, caso a ação seja executada com sucesso, ou false, caso contrário.
                             */
                            bool actionRequest(UPnPAction *action);

                            /**
                             * Envia o estado atual de uma variável do serviço.
                             * @param stateVar variável solicitada.
                             * @return true, caso a ação seja executada com sucesso, ou false, caso contrário.
                             */
                            bool variableRequest(UPnPStateVariable *stateVar);

                            /**
                             * Recebe uma mensagem (texto) de um dispositivo remoto.
                             * @param action ação a ser executada.
                             * @return true, caso a ação seja executada com sucesso, ou false, caso contrário.
                             */
                            bool actionPostEvent(UPnPAction *action);

                        };

                }
            }
        }
    }
}

#endif	/* _MMISERVICE_H */
