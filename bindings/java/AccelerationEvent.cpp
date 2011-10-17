#include <jni.h>
#include "br_ufscar_lince_mmi_AccelerationEvent.h"

#include "Util.h"

#include "../../include/AccelerationEvent.h"
using namespace ::br::ufscar::lince::mmi;


JNIEXPORT jint JNICALL Java_br_ufscar_lince_mmi_AccelerationEvent_getXValue
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	AccelerationEvent* accEvent = (AccelerationEvent*) event;
	return (jint) accEvent->getXValue();
}

JNIEXPORT jint JNICALL Java_br_ufscar_lince_mmi_AccelerationEvent_getYValue
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	AccelerationEvent* accEvent = (AccelerationEvent*) event;
	return (jint) accEvent->getYValue();
}

JNIEXPORT jint JNICALL Java_br_ufscar_lince_mmi_AccelerationEvent_getZValue
  	  (JNIEnv *jenv, jobject jobj) {

	MMIEvent* event = getMMIEvent(jenv, jobj);
	AccelerationEvent* accEvent = (AccelerationEvent*) event;
	return (jint) accEvent->getZValue();
}
