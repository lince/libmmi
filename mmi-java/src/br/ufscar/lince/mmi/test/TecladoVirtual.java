package br.ufscar.lince.mmi.test;

import java.util.Set;
import java.util.TreeSet;
import br.ufscar.lince.mmi.*;

import java.awt.Robot;
import java.awt.AWTException;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;

import java.math.*;


public class TecladoVirtual extends MMIEventListener {
	
    Robot r;
	TecladoVirtual() {
		super();
		try {
			r = new Robot();
		} catch (AWTException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		positionX = 500;
		positionY = 400;
	}

	public static void main(String[] args) throws InterruptedException {
		
		System.out.println("\t\tJAVA - Vamos começar o MMIManager");
		MMIManager manager = MMIManager.getInstance();
		
		System.out.println("\t\tJAVA - Criando o Listener");
		TecladoVirtual lister = new TecladoVirtual();
		
		Set<String> eventTypes = new TreeSet<String>();
		eventTypes.add("key");
		eventTypes.add("acceleration");
		
		System.out.println("\t\tJAVA - Registrando o Listener");
		manager.addEventListener(lister, eventTypes);
		
		System.out.println("\t\tJAVA - Esperando");
		
		manager.connectWiiMote();

		while(true) {
			Thread.sleep(3000);
		}
	}

	@Override
	public boolean receiveEvent(MMIEvent event) {
		String stype = event.getEventType();
		//System.out.println("EventType: " + stype);
		if (stype.equals("key")) {
			try{
				br.ufscar.lince.mmi.KeyEvent keyEvent = 
						br.ufscar.lince.mmi.KeyEvent.CovertEvent(event);
				
				String value = keyEvent.getKeyId();
				System.out.println("Tecla pressionada: " + value);
				int keyCode = mapVK(value);
				System.out.println("keyCode = " + keyCode);
				r.keyPress(keyCode);
				r.delay(100);
				r.keyRelease(keyCode);
			} catch (Exception e) {
				e.printStackTrace();
			}
		
		} else if (stype.equals("acceleration")) {
			try {
				AccelerationEvent accEvent = AccelerationEvent.CovertEvent(event);
				handleAcceleration(accEvent);
				//System.out.println();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return true;
	}
	
	private int positionX;
	private int positionY;

	private void handleAcceleration(AccelerationEvent accEvent) {
		int accX = accEvent.getXValue();
		int accY = accEvent.getYValue();
		if (accX < 115 || accX > 130) {
			positionX += (accX - 125)*2;
		}
		if (accY < 115 || accY > 130) {
			positionY += (accY - 125)*2;
		}	
		if (positionX < 0) {
			positionX = 0;
		} else if (positionX > 1280) {
			positionX = 1280;
		} else if (positionY > 1024) {
			positionY = 1024;
		}
		
		if (positionY < 0) {
			positionY = 0;
		}
		r.mouseMove(positionX, positionY);
	}

	private int mapVK(String value) {
		int ret = 0;
		if (value.equals("KEY_A")) {
			ret = KeyEvent.VK_A;
		} else if (value.equals("KEY_B")) {
			ret = KeyEvent.VK_B;
		} else if (value.equals("KEY_C")) {
			ret = KeyEvent.VK_C;
		} else if (value.equals("KEY_D")) {
			ret = KeyEvent.VK_D;
		} else if (value.equals("KEY_E")) {
			ret = KeyEvent.VK_E;
		} else if (value.equals("KEY_F")) {
			ret = KeyEvent.VK_F;
		} else if (value.equals("KEY_G")) {
			ret = KeyEvent.VK_G;
		} else if (value.equals("KEY_H")) {
			ret = KeyEvent.VK_H;
		} else if (value.equals("KEY_I")) {
			ret = KeyEvent.VK_I;
		} else if (value.equals("KEY_J")) {
			ret = KeyEvent.VK_J;
		} else if (value.equals("KEY_K")) {
			ret = KeyEvent.VK_K;
		} else if (value.equals("KEY_L")) {
			ret = KeyEvent.VK_L;
		} else if (value.equals("KEY_M")) {
			ret = KeyEvent.VK_M;
		} else if (value.equals("KEY_N")) {
			ret = KeyEvent.VK_N;
		} else if (value.equals("KEY_O")) {
			ret = KeyEvent.VK_O;
		} else if (value.equals("KEY_P")) {
			ret = KeyEvent.VK_P;
		} else if (value.equals("KEY_Q")) {
			ret = KeyEvent.VK_Q;
		} else if (value.equals("KEY_R")) {
			ret = KeyEvent.VK_R;
		} else if (value.equals("KEY_S")) {
			ret = KeyEvent.VK_S;
		} else if (value.equals("KEY_T")) {
			ret = KeyEvent.VK_T;
		} else if (value.equals("KEY_U")) {
			ret = KeyEvent.VK_U;
		} else if (value.equals("KEY_V")) {
			ret = KeyEvent.VK_V;
		} else if (value.equals("KEY_X")) {
			ret = KeyEvent.VK_X;
		} else if (value.equals("KEY_Y")) {
			ret = KeyEvent.VK_Y;
		} else if (value.equals("KEY_W")) {
			ret = KeyEvent.VK_W;
		} else if (value.equals("KEY_Z")) {
			ret = KeyEvent.VK_Z;
		} else if (value.equals("KEY_1")) {
			ret = KeyEvent.VK_1;
		} else if (value.equals("KEY_2")) {
			ret = KeyEvent.VK_2;
		} else if (value.equals("KEY_3")) {
			ret = KeyEvent.VK_3;
		} else if (value.equals("KEY_4")) {
			ret = KeyEvent.VK_4;
		} else if (value.equals("KEY_5")) {
			ret = KeyEvent.VK_5;
		} else if (value.equals("KEY_6")) {
			ret = KeyEvent.VK_6;
		} else if (value.equals("KEY_7")) {
			ret = KeyEvent.VK_7;
		} else if (value.equals("KEY_8")) {
			ret = KeyEvent.VK_8;
		} else if (value.equals("KEY_9")) {
			ret = KeyEvent.VK_9;
		} else if (value.equals("KEY_0")) {
			ret = KeyEvent.VK_0;
		} else if (value.equals("WII_BUTTON_LEFT")) {
			ret = KeyEvent.VK_A;
		} else if (value.equals("WII_BUTTON_UP")) {
			ret = KeyEvent.VK_W;
		} else if (value.equals("WII_BUTTON_RIGHT")) {
			ret = KeyEvent.VK_D;
		} else if (value.equals("WII_BUTTON_DOWN")) {
			ret = KeyEvent.VK_S;
		} else if (value.equals("WII_BUTTON_MINUS")) {
			r.mousePress(InputEvent.BUTTON1_MASK);
			r.mouseRelease(InputEvent.BUTTON1_MASK);
		} else if (value.equals("WII_BUTTON_PLUS")) {
			r.mousePress(InputEvent.BUTTON2_MASK);
			r.mouseRelease(InputEvent.BUTTON2_MASK);
		}
		return ret;
	}
}