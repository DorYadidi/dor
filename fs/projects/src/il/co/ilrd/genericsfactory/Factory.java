package il.co.ilrd.genericsfactory;

import java.util.HashMap;
import java.util.function.Function;


public class Factory <K, T, D> {

	private HashMap<K, Function<D, T>> mapConstructor = new HashMap<>();
	
	public T create(K key) {
		return create(key, null);
	}
	
	public T create(K key, D data) {
		return mapConstructor.get(key).apply(data);
	}
	
	public Function<D, T> add (K key, Function<D, T> func) {
		return mapConstructor.put(key, func);
	}
}
