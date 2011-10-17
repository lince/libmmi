#include <jni.h>
#include "../../include/MMIEventListener.h"
using namespace ::br::ufscar::lince::mmi;

#include <linceutil/LoggerUtil.h>
using namespace br::ufscar::lince::util;

class EventListenerAdapter : public MMIEventListener {
public:
	static EventListenerAdapter* GetEventListenerAdapter(
			JNIEnv *jenv, jobject jevent);

	bool receiveEvent(MMIEvent* event);

	EventListenerAdapter(JNIEnv *jenv, jobject jevent);

	~EventListenerAdapter();

private:
	static JavaVM* javaVM; //criar maneira de inicialização

	jobject jlisterObject; //Obter no Construtor
	jclass jObjectClass; //Obter no Construtor
	jmethodID jmethodReceiveEvent; //Obter no Construtor
	jmethodID jmethodFinalize; //Obter no Construtor
	jclass jMMIEventClass; //criar maneira de inicialização
	jmethodID jEventConstructor; //criar maneira de inicialização

	HLoggerPtr logger;
};
