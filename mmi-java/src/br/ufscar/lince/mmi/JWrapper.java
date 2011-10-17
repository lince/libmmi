package br.ufscar.lince.mmi;

abstract class JWrapper {
	static {
		System.loadLibrary("mmijava");
	}
	
	protected long pointer;
}
