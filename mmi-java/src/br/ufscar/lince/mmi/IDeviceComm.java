package br.ufscar.lince.mmi;

import java.util.Vector;

public abstract class IDeviceComm extends JWrapper {
	
	public IDeviceComm(String deviceId) {
		this.pointer = create(deviceId);
	}
	
	public void finalize() {
		destroy();
	}
	
	public abstract void connect();
	public abstract void disconnect();
	public abstract void sendToDevice(Vector<String> args);
	public abstract String getDeviceId();
	public abstract void release();
	
	private native long create(String deviceId);
	private native void destroy();
}
