package br.ufscar.lince.mmi;

public class AccelerationEvent extends MMIEvent {

	protected AccelerationEvent(long pointer) {
		super(pointer);
	}
	
	public native int getXValue();

	public native int getYValue();

	public native int getZValue();
	
	static public AccelerationEvent CovertEvent(MMIEvent event) throws Exception {
		if (!event.getEventType().equals("acceleration")) {
			throw new Exception("Event ins't a AccelerationEvent.");
		}
		return new AccelerationEvent(event.pointer);
	}
}
