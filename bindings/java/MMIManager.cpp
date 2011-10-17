#include <jni.h>
#include "br_ufscar_lince_mmi_MMIManager.h"

#include "../../include/MMIManager.h"
using namespace ::br::ufscar::lince::mmi;

#include "JavaEventAdapter.h"
#include "JavaDeviceAdapter.h"
#include "EventListenerAdapter.h"

MMIManager* getMMIManager(JNIEnv *jenv, jobject jobj) {
	jclass cls = jenv->GetObjectClass(jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = jenv->GetFieldID(cls, "pointer", "J");
		if (fid == NULL) {
			return NULL;
		}
	}
	return (MMIManager*)jenv->GetLongField(jobj, fid);
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_release
  	  (JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	manager->release();
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_connectWiiMote
  (JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	manager->connectWiiMote();
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_postEvent
  	  (JNIEnv *jenv, jobject jobj, jobject jevent) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	JavaEventAdapter* event = JavaEventAdapter::GetJavaEventAdapter(jenv, jevent);
	manager->postEvent(event);
}


JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_postXMLEvent
  	  	(JNIEnv *jenv, jobject jobj, jcharArray jdata) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	XMLData* data = new XMLData();
	data->payload = (char*) jenv->GetCharArrayElements(jdata, 0);
	data->length = (int) jenv->GetArrayLength((jarray) jdata);
	manager->postXMLEvent(data);

}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_registerDevice
  	  (JNIEnv *jenv, jobject jobj, jobject jdevice, jstring jdeviceId) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	IDeviceComm* device = JavaDeviceAdapter::GetJavaDeviceAdapter(jenv, jdevice);
	string deviceId = jenv->GetStringUTFChars(jdeviceId, 0);
	manager->registerDevice(device, deviceId);
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_unregisterDevice
  	  (JNIEnv *jenv, jobject jobj, jstring jdeviceId) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	string deviceId = jenv->GetStringUTFChars(jdeviceId, 0);
	manager->unregisterDevice(deviceId);
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_doAddEventListener
  	  (JNIEnv *jenv, jobject jobj, jobject jeventListener, jobjectArray jeventTypes) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	MMIEventListener* listener =
			EventListenerAdapter::GetEventListenerAdapter(jenv, jeventListener);

	set<string>* eventTypes = new set<string>();
	int size = jenv->GetArrayLength(jeventTypes);
	for (int i = 0; i < size; i++) {
		jstring jaux = (jstring) jenv->GetObjectArrayElement(jeventTypes, i);
		string aux = jenv->GetStringUTFChars(jaux, 0);
		eventTypes->insert(aux);
	}
	manager->addEventListener(listener, eventTypes);
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_removeEventListener
  	  (JNIEnv *jenv, jobject jobj, jobject jeventListener) {

	MMIManager* manager = getMMIManager(jenv, jobj);
		MMIEventListener* listener =
				EventListenerAdapter::GetEventListenerAdapter(jenv, jeventListener);
		manager->removeEventListener(listener);

}

JNIEXPORT jobjectArray JNICALL Java_br_ufscar_lince_mmi_MMIManager_doGetDevicesName
  	  (JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	vector<string>* devicesName = manager->getDevicesName();
	static jclass jstringClass = jenv->FindClass("java.lang.String");
	static jmethodID stringConstructor = jenv->GetMethodID(
			jstringClass, "<init>", "void (V)");
	jobject jdefaultString = jenv->NewObject(jstringClass, stringConstructor);
	jobjectArray jarray = jenv->NewObjectArray(devicesName->size(),
			jstringClass, jdefaultString);

	for (int i = 0; i < devicesName->size() ; i++) {
		jstring jaux = jenv->NewStringUTF(devicesName->at(i).c_str());
		jenv->SetObjectArrayElement(jarray, i, jaux);
	}
	return jarray;
}


JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_doCallDeviceService
  	  (JNIEnv *jenv, jobject jobj, jstring jdeviceId, jobjectArray jargs) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	string deviceId = jenv->GetStringUTFChars(jdeviceId, 0);

	vector<string>* args = new vector<string>();
	int size = jenv->GetArrayLength(jargs);
	for (int i = 0; i < size; i++) {
		jstring jaux = (jstring) jenv->GetObjectArrayElement(jargs, i);
		string aux = jenv->GetStringUTFChars(jaux, 0);
		((*args)[i]) = aux;
	}
	manager->callDeviceService(deviceId, args);
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_waitForUnlockCondition
  	  (JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	manager->waitForUnlockCondition();
}

JNIEXPORT jlong JNICALL Java_br_ufscar_lince_mmi_MMIManager_create
		(JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = MMIManager::getInstance();
	return (jlong) manager;
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_MMIManager_destroy
  	  (JNIEnv *jenv, jobject jobj) {

	MMIManager* manager = getMMIManager(jenv, jobj);
	manager->release();
}
