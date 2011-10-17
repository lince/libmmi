#include <jni.h>
#include "br_ufscar_lince_mmi_MMIEventListener.h"
#include "EventListenerAdapter.h"

#include <iostream>
using namespace std;

#include "../../include/MMIEventListener.h"
using namespace ::br::ufscar::lince::mmi;

JavaVM* EventListenerAdapter::javaVM = NULL;

EventListenerAdapter::EventListenerAdapter(JNIEnv *jenv, jobject jevent) {
	logger = LoggerUtil::getLogger(
					"br.ufscar.lince.mmi.bindings.java.EventListenerAdapter");

	LoggerUtil_info(logger, "Construtor");

	if (!javaVM) {
		javaVM = new JavaVM();
		int result = jenv->GetJavaVM(&javaVM);
		if (result < 0) {
			cerr<<"Error getting the JavaVM";
			//TODO: throw Exception.
		}
	}
}

EventListenerAdapter::~EventListenerAdapter() {
	LoggerUtil_info(logger, "Destrutor");

	JNIEnv* jenv = new JNIEnv();

	int erro = (int) javaVM->GetEnv((void**) &jenv, JNI_VERSION_1_2);
	if (erro == JNI_EDETACHED) {
		//cerr<<"ERRO OBTENDO a jenv!!! - JNI_EDETACHED."<<endl;
		if (javaVM->AttachCurrentThread((void**) &jenv, NULL) < 0) {
			cerr<<"ERRO Associando uma nova thread!!! - JNI_EDETACHED."<<endl;
		}

	} else if (erro == JNI_EVERSION) {
		cerr<<"ERRO OBTENDO a jenv!!! - JNI_EVERSION."<<endl;
	}

}

EventListenerAdapter* EventListenerAdapter::GetEventListenerAdapter(
		JNIEnv *jenv, jobject jobj) {

	jclass cls = jenv->GetObjectClass(jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = jenv->GetFieldID(cls, "pointer", "J");
		if (fid == NULL) {
			return NULL;
		}
	}
	return (EventListenerAdapter*)jenv->GetLongField(jobj, fid);
}

bool EventListenerAdapter::receiveEvent(MMIEvent* event) {

	LoggerUtil_info(logger, "receiveEvent(MMIEvent* event)");

	JNIEnv* jenv = new JNIEnv();

	int erro = (int) javaVM->GetEnv((void**) &jenv, JNI_VERSION_1_2);
	if (erro == JNI_EDETACHED) {
		//cerr<<"ERRO OBTENDO a jenv!!! - JNI_EDETACHED."<<endl;
		if (javaVM->AttachCurrentThread((void**) &jenv, NULL) < 0) {
			cerr<<"ERRO Associando uma nova thread!!! - JNI_EDETACHED."<<endl;
		}

	} else if (erro == JNI_EVERSION) {
		cerr<<"ERRO OBTENDO a jenv!!! - JNI_EVERSION."<<endl;
	}

	jMMIEventClass = jenv->FindClass("br/ufscar/lince/mmi/MMIEvent");
	if (!jMMIEventClass) {
		cerr<<"Classe do event retornou NULL"<<endl;
		//TODO: throw exception
	}

	jEventConstructor = jenv->GetMethodID(jMMIEventClass, "<init>", "(J)V");
	jobject jevent = jenv->NewObject(jMMIEventClass, jEventConstructor, (jlong) event);

	if (jevent == NULL) {
		cerr<<"JavaEventAdapter::receiveEvent - Erro ao criar um jMMIEvent"<<endl;
		//TODO: throw exception em java
	}
	jObjectClass = jenv->FindClass("br/ufscar/lince/mmi/MMIEventListener");
	//cerr<<"EventListenerAdapter::receiveEvent - obtendo a classe (OK)"<<endl;

	jmethodID getObjectMethod = jenv->GetStaticMethodID(jObjectClass,
			"GetJavaObject", "(J)Lbr/ufscar/lince/mmi/MMIEventListener;");
	//cerr<<"EventListenerAdapter::receiveEvent - obtendo o metodo "
	//		"GetJavaObject (OK):"<<getObjectMethod<<endl;

	jlisterObject = jenv->CallStaticObjectMethod(jObjectClass,
			getObjectMethod, (jlong) this);
	//cerr<<"EventListenerAdapter::receiveEvent - obtendo a"
	//		" instância do objeto java:"<<jlisterObject<<endl;

	jmethodReceiveEvent = jenv->GetMethodID(jObjectClass,
				"receiveEvent", "(Lbr/ufscar/lince/mmi/MMIEvent;)Z");
	//cerr<<"EventListenerAdapter::receiveEvent - obtendo o método receiveEvent"<<endl;

	bool returnValue = (bool) jenv->CallBooleanMethod(
			jlisterObject, jmethodReceiveEvent, jevent);

	//cerr<<"EventListenerAdapter::receiveEvent - Event enviado para java. Returno"<<
	//		returnValue<<endl;

	return returnValue;
}

JNIEXPORT jlong JNICALL Java_br_ufscar_lince_mmi_MMIEventListener_create
  	  (JNIEnv *jenv, jobject jobject) {

	EventListenerAdapter* listenerAdapter = new EventListenerAdapter(jenv, jobject);
	return (jlong) listenerAdapter;
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIEventListener_destroy
  	  (JNIEnv *jenv, jobject jobject) {

	EventListenerAdapter* listenerAdapter =
			EventListenerAdapter::GetEventListenerAdapter(jenv, jobject);

	delete listenerAdapter;
}
