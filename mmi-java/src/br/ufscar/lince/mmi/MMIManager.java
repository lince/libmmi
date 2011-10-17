package br.ufscar.lince.mmi;

import java.util.Set;
import java.util.Vector;

public class MMIManager extends JWrapper {
	
	static private MMIManager _instance = null;
	
	private MMIManager() {
		this.pointer = create();
	}
	
	protected void finalize() {
		destroy();
	}
	
	public static MMIManager getInstance() {
		if (_instance == null) {
			_instance = new MMIManager();
		}
		return _instance;
	}

	native public void release();
	
	native public void connectWiiMote();
		
	//precisa criar um adaptador
	native public void postEvent(MMIEvent event); 
	
	native public void postXMLEvent(char[] event);

	//precisa criar um adaptador
	native public void registerDevice(IDeviceComm device, String deviceId); 

	native public void unregisterDevice(String deviceId);

	//precisa criar um adaptador
	public void addEventListener(MMIEventListener listener, 
			Set<String> eventTypes) {
		
		String[] arrayTypes = new String[eventTypes.size()];
		int i = 0;
		for (String aux : eventTypes) {
			arrayTypes[i] = aux;
			i++;
		}
		doAddEventListener(listener, arrayTypes);
	}

	//precisa criar um adaptador
	native public void removeEventListener(MMIEventListener listener);

	public Vector<String> getDevicesName() {
		String[] devicesNames = doGetDevicesName();
		Vector<String> ret = new Vector<String>();
		for (String aux : devicesNames) {
			ret.add(aux);
		}
		return ret;
	}

	public void callDeviceService(String deviceId, Vector<String> args) {
		
		String[] arrayArgs = new String[args.size()];
		int i = 0;
		for (String aux : args) {
			arrayArgs[i] = aux;
			i++;
		}
		doCallDeviceService(deviceId, arrayArgs);
	}

	public native void waitForUnlockCondition();
	
	
	private native long create();
	
	private native void destroy();
	
	private native void doAddEventListener(MMIEventListener listener, 
			String[] eventTypes);
	
	private native void doCallDeviceService(String deviceId, String[] arrayArgs);
	
	private native String[] doGetDevicesName();

}