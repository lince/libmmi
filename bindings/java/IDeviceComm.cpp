#include <jni.h>
#include "br_ufscar_lince_mmi_IDeviceComm.h"
#include "JavaDeviceAdapter.h"

#include <iostream>
using namespace std;

#include "../../include/IDeviceComm.h"
using namespace ::br::ufscar::lince::mmi;

JNIEnv* JavaDeviceAdapter::javaEnv = NULL;

JavaDeviceAdapter* JavaDeviceAdapter::GetJavaDeviceAdapter(
		JNIEnv *jenv, jobject jobj) {
	jclass cls = jenv->GetObjectClass(jobj);
	static jfieldID fid = NULL;
	if (fid == NULL) {
		fid = jenv->GetFieldID(cls, "pointer", "J");
		if (fid == NULL) {
			return NULL;
		}
	}
	return (JavaDeviceAdapter*)jenv->GetLongField(jobj, fid);
}

//TODO: implementar todos os métodos e verificar o deviceId passado no construtor java

JavaDeviceAdapter::JavaDeviceAdapter(JNIEnv *jenv, jobject jdevice) {
	if (javaEnv == NULL) {
		javaEnv = jenv;
	}
	jDevice = jdevice;
}

JavaDeviceAdapter::~JavaDeviceAdapter() {

}

void JavaDeviceAdapter::connect() {

}

void JavaDeviceAdapter::disconnect() {

}

void JavaDeviceAdapter::sendToDevice(vector<string>* args) {

}

string JavaDeviceAdapter::getDeviceId() {

}

void JavaDeviceAdapter::release() {

}
JNIEXPORT jlong JNICALL Java_br_ufscar_lince_mmi_IDeviceComm_create
		(JNIEnv *jenv, jobject jobj, jstring deviceId) {

	JavaDeviceAdapter* deviceAdapter = new JavaDeviceAdapter(jenv, jobj);
	return (jlong) deviceAdapter;
}

JNIEXPORT void JNICALL Java_br_ufscar_lince_mmi_IDeviceComm_destroy
		(JNIEnv *jenv, jobject jobj) {

	JavaDeviceAdapter* deviceAdapter =
			JavaDeviceAdapter::GetJavaDeviceAdapter(jenv, jobj);

	delete deviceAdapter;
}
