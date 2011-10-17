package br.ufscar.lince.mmi;

public class MMIEvent extends JWrapper {
	
	protected MMIEvent(long pointer) {
		this.pointer = pointer;
	}
	
	public void finalize() {
		destroy();
	}
	
	public native String getDeviceId();
	
	public native String getEventType();
	
	private native void destroy();
	
	static public MMIEvent CovertEvent(MMIEvent event) throws Exception {
		throw new Exception("You should'nt call this method with an superclass MMIEvent " +
				"instance. Use its subclasses instead");
	}
}
