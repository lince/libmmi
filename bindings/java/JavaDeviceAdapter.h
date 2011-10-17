#include <jni.h>
#include "../../include/IDeviceComm.h"
using namespace ::br::ufscar::lince::mmi;

class JavaDeviceAdapter : public IDeviceComm {
public:
	static JavaDeviceAdapter* GetJavaDeviceAdapter(
			JNIEnv *jenv, jobject jdevice);

	JavaDeviceAdapter(JNIEnv *jenv, jobject jdevice);

	~JavaDeviceAdapter();

	void connect();

	void disconnect();

	void sendToDevice(vector<string>* args);

	string getDeviceId();

	void release();

private:
	static JNIEnv* javaEnv;
	static jmethodID methodConnect;
	static jmethodID methodDisconnect;
	static jmethodID methodSendToDevice;
	static jmethodID methodGetDeviceId;
	static jmethodID methodRelease;

	jobject jDevice;
	jclass jDeviceClass;
};
