package il.co.ilrd.gatewayserver;

import java.io.Serializable;

public class Packet<K, D> implements Serializable{
	private static final long serialVersionUID = 1L;
	private K key;
	private D data;
	
	public Packet(K key, D data) {
		this.key = key;
		this.data = data;
	}

	public K getKey() {
		return key;
	}

	public D getData() {
		return data;
	}
}

