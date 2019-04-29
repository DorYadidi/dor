package il.co.ilrd.observer;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class Dispatcher<T> {
	private List<Callback<T>> table = new LinkedList<>();

	public void register(Callback<T> observer) {
		Objects.requireNonNull(observer, "null observer");

		table.add(observer);
		observer.registerDispatcher(this);
	}

	public void unregister(Callback<T> observer) {
		Objects.requireNonNull(observer, "null observer");
		
		table.remove(observer);
		observer.unregisterDispatcher();
	}

	public void notifyObservers(T data) {
		for (Callback<T> observer : table) {
			observer.update(data);
		}
	}

	public void terminate() {
		Iterator<Callback<T>> runner = table.iterator();
		while (runner.hasNext()) {
			Callback<T> removed = runner.next();
			runner.remove();
			removed.terminate();
			removed.unregisterDispatcher();
		}
	}
}
