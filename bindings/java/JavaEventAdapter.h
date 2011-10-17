#include <jni.h>
#include "../../include/MMIEvent.h"
using namespace ::br::ufscar::lince::mmi;

class JavaEventAdapter : public MMIEvent {
public:
	static JavaEventAdapter* GetJavaEventAdapter(
			JNIEnv *jenv, jobject jevent);

	JavaEventAdapter(JNIEnv *jenv, jobject jevent,
			string deviceId, string eventType);

	~JavaEventAdapter();

private:
	static JavaVM* javaVM;
};
