package br.ufscar.lince.mmi;

import java.util.HashMap;
import java.util.Map;

public abstract class MMIEventListener extends JWrapper {
	
	private static Map<Long, MMIEventListener> listenerMap;
	
	static {
		listenerMap = new HashMap<Long, MMIEventListener>();
	}
	
	private static MMIEventListener GetJavaObject(long pointer) {
		return listenerMap.get(pointer);
	}

	public abstract boolean receiveEvent(MMIEvent event);
	
	public MMIEventListener() {
		this.pointer = create();
		listenerMap.put(this.pointer, this);
	}
	
	public void finalize() {
		destroy();
		listenerMap.remove(this.pointer);
	}
	
	protected native long create();
	
	protected native void destroy();
}
