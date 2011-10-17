package br.ufscar.lince.mmi;

public class KeyEvent extends MMIEvent {

	protected KeyEvent(long pointer) {
		super(pointer);
	}
	
	public native String getKeyId();
	
	static public KeyEvent CovertEvent(MMIEvent event) throws Exception {
		if (!event.getEventType().equals("key")) {
			throw new Exception("Event ins't a KeyEvent.");
		}
		return new KeyEvent(event.pointer);
	}
}
