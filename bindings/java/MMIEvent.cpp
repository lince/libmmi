#include <jni.h>
#include "br_ufscar_lince_mmi_MMIEvent.h"
#include "br_ufscar_lince_mmi_JavaEvent.h"

#include "Util.h"

#include <iostream>
using namespace std;

#include "../../include/MMIEvent.h"
using namespace ::br::ufscar::lince::mmi;

#include "JavaEventAdapter.h"

JavaVM* JavaEventAdapter::javaVM = NULL;

JavaEventAdapter* JavaEventAdapter::GetJavaEventAdapter(
		JNIEnv *jenv, jobject jobj) {

	jclass cls = jenv->GetObjectClass(jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = jenv->GetFieldID(cls, "pointer", "J");
		if (fid == NULL) {
			return NULL;
		}
	}
	return (JavaEventAdapter*)jenv->GetLongField(jobj, fid);
}

JavaEventAdapter::JavaEventAdapter(JNIEnv *jenv, jobject jevent,
		string deviceId, string eventType) : MMIEvent(deviceId, eventType) {

	if (!javaVM) {
		javaVM = new JavaVM();
		int result = jenv->GetJavaVM(&javaVM);
		if (result < 0) {
			cerr<<"Error getting the JavaVM";
			//TODO: throw Exception.
		}
	}
}

JavaEventAdapter::~JavaEventAdapter() {
	//TODO: destruir o evento

}

JNIEXPORT jlong JNICALL Java_br_ufscar_lince_mmi_JavaEvent_create
  	  (JNIEnv *jenv, jclass jclass, jstring jdeviceId, jstring jeventType) {

	string deviceId = jenv->GetStringUTFChars(jdeviceId, 0);
	string eventType = jenv->GetStringUTFChars(jeventType, 0);

	JavaEventAdapter* event = new JavaEventAdapter(jenv, jclass, deviceId, eventType);
	return (jlong) event;
}

MMIEvent* getMMIEvent(JNIEnv *jenv, jobject jobj) {
	jclass cls = jenv->GetObjectClass(jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = jenv->GetFieldID(cls, "pointer", "J");
		if (fid == NULL) {
			return NULL;
		}
	}
	return (MMIEvent*)jenv->GetLongField(jobj, fid);
}

JNIEXPORT jstring JNICALL Java_br_ufscar_lince_mmi_MMIEvent_getDeviceId
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	string str = event->getDeviceId();
	jstring jStr = jenv->NewStringUTF(str.c_str());
	return jStr;
}

JNIEXPORT jstring JNICALL Java_br_ufscar_lince_mmi_MMIEvent_getEventType
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	string str = event->getEventType();
	jstring jStr = jenv->NewStringUTF(str.c_str());
	return jStr;
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIEvent_destroy
  	  (JNIEnv *jenv, jobject jobj) {

	//TODO: Testar a deleção dos eventos
	//MMIEvent* event = getMMIEvent(jenv, jobj);
	//delete event;
}
