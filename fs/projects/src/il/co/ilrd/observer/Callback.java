package il.co.ilrd.observer;

import java.util.function.Consumer;
import java.util.Objects; 

public class Callback<T> {
	private Consumer<T> update;
	private Runnable terminate;
	private Dispatcher<T> dispatcher;

	public Callback(Consumer<T> update, Runnable terminate) {
		Objects.requireNonNull(update, "null update");
		Objects.requireNonNull(terminate, "null terminate");
		
		this.update = update;
		this.terminate = terminate;
	}

	public void update(T data) {
		update.accept(data);
	}

	public void setUpdate(Consumer<T> update) {
		Objects.requireNonNull(update, "null update");

		this.update = update;
	}

	public void setTerminate(Runnable terminate) {
		Objects.requireNonNull(terminate, "null terminate");

		this.terminate = terminate;
	}

	public void terminate() {
		terminate.run();
	}

	public void registerDispatcher(Dispatcher<T> dispatcher) {
		this.dispatcher = dispatcher;
	}

	public void unregisterDispatcher() {
		dispatcher = null;
	}

	public void unregisterCallback() {
		dispatcher.unregister(this);
	}
}
