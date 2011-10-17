#include <jni.h>
#include "br_ufscar_lince_mmi_KeyEvent.h"

#include "Util.h"

#include "../../include/KeyEvent.h"
using namespace ::br::ufscar::lince::mmi;

JNIEXPORT jstring JNICALL Java_br_ufscar_lince_mmi_KeyEvent_getKeyId
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	KeyEvent* keyEvent = (KeyEvent*) event;
	string keyId = keyEvent->getKeyId();
	jstring jkeyId = jenv->NewStringUTF(keyId.c_str());
	return jkeyId;
}
