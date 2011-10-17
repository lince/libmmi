package br.ufscar.lince.mmi;

public class JavaEvent extends MMIEvent {

	protected JavaEvent(String deviceId, String eventType) {
		super(create(deviceId, eventType));
	}
	
	private native static long create(String deviceId, String eventType);
	
	//TODO: criar meios para que as aplicações em C possam acessar os eventos
}
