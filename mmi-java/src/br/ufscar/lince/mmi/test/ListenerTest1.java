package br.ufscar.lince.mmi.test;

import java.util.Set;

import java.util.TreeSet;

import br.ufscar.lince.mmi.*;

class FakeEvent extends JavaEvent {

	FakeEvent(int value) {
		super("javadevice", "javaevent");
		this.value = value;
	}
	
	int value;
}

public class ListenerTest1 extends MMIEventListener {
	
	ListenerTest1() {
		super();
	}

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("\t\tJAVA - Vamos começar o MMIManager");
		MMIManager manager = MMIManager.getInstance();
		
		System.out.println("\t\tJAVA - Criando o Listener");
		ListenerTest1 lister = new ListenerTest1();
		
		Set<String> eventTypes = new TreeSet<String>();
		eventTypes.add("key");
		eventTypes.add("javaevent");
		
		System.out.println("\t\tJAVA - Registrando o Listener");
		manager.addEventListener(lister, eventTypes);
		
		System.out.println("\t\tJAVA - Esperando");
		for (int i = 0; i < 5; i++) {
			Thread.sleep(3000);
			FakeEvent event = new FakeEvent(i);
			manager.postEvent(event);
		}
		/*while(true) {
			Thread.sleep(3000);
		}*/
	}

	@Override
	public boolean receiveEvent(MMIEvent event) {
		String stype = event.getEventType();
		System.out.println("EventType: " + stype);
		if (stype.equals("key")) {
			try{
				KeyEvent keyEvent = KeyEvent.CovertEvent(event);
				System.out.println("Tecla pressionada: " + keyEvent.getKeyId());
			} catch (Exception e) {
				e.printStackTrace();
			}
		} else if (stype.equals("javaevent")) {
				FakeEvent jEvent = (FakeEvent) event;
				System.out.println("Valor: " + jEvent.value);
		}
		return true;
	}

}
